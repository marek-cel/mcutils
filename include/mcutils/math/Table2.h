/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
#ifndef MCUTILS_MATH_TABLE2_H_
#define MCUTILS_MATH_TABLE2_H_

#include <cmath>
#include <limits>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <units.h>

#include <mcutils/math/Table.h>

#include <mcutils/misc/Check.h>
#include <mcutils/misc/StringUtils.h>

using namespace units::math;

namespace mc {

/**
 * \brief 2D table and bilinear interpolation class template.
 */
template <typename ROW_TYPE, typename COL_TYPE, typename VAL_TYPE>
class Table2
{
public:

    /** \brief Copy constructor. */
    Table2(const Table2<ROW_TYPE,COL_TYPE,VAL_TYPE>& table)
        : _rows(table._rows)
        , _cols(table._cols)
        , _size(table._size)
    {
        if (_size > 0)
        {
            createArrays();

            for (unsigned int i = 0; i < _rows; ++i) _row_values[i] = table._row_values[i];
            for (unsigned int i = 0; i < _cols; ++i) _col_values[i] = table._col_values[i];

            for (unsigned int i = 0; i < _size; ++i)
            {
                _table_data[i] = table._table_data[i];
                _inter_data[i] = table._inter_data[i];
            }
        }
    }

    /** \brief Move constructor. */
    Table2(Table2<ROW_TYPE,COL_TYPE,VAL_TYPE>&& table) noexcept
        : _rows(std::exchange(table._rows, 0))
        , _cols(std::exchange(table._cols, 0))
        , _size(std::exchange(table._size, 0))

        , _row_values(std::exchange(table._row_values, nullptr))
        , _col_values(std::exchange(table._col_values, nullptr))
        , _table_data(std::exchange(table._table_data, nullptr))

        , _inter_data(std::exchange(table._inter_data, nullptr))
    {}

    /**
     * \brief Constructor.
     * Creates table with only one record.
     * \param val record value
     * \param row_val row key value
     * \param col_val col key value
     */
    Table2(VAL_TYPE val = VAL_TYPE{0},
           ROW_TYPE row_val = ROW_TYPE{0},
           COL_TYPE col_val = COL_TYPE{0})
    {
        _rows = 1;
        _cols = 1;
        _size = 1;

        createArrays();

        _row_values[0] = row_val;
        _col_values[0] = col_val;
        _table_data[0] = val;
        _inter_data[0] = 0.0;

        updateInterpolationData();
    }

    /**
     * \brief Constructor.
     *
     * This constructor is used to initialize table with data.
     * Table data index should match following scheme i = i_row * no_of_columns + i_col
     *
     * \param row_values rows key values ordered vector
     * \param col_values columns key values ordered vector
     * \param table_data table values ordered vector
     */
    Table2(const std::vector<ROW_TYPE>& row_values,
           const std::vector<COL_TYPE>& col_values,
           const std::vector<VAL_TYPE>& table_data)
    {
        setData(row_values, col_values, table_data);
    }

    /** \brief Destructor. */
    ~Table2()
    {
        deleteArrays();
    }

    /**
     * \brief Returns 1-dimensional table for the given col value.
     * \param colValue column key value
     * \return 1-dimensional table
     */
    Table<ROW_TYPE,VAL_TYPE> getTable(COL_TYPE col_value) const
    {
        std::vector<ROW_TYPE> keyValues;
        std::vector<VAL_TYPE> tableData;

        for (unsigned int i = 0; i < _rows; ++i)
        {
            keyValues.push_back(_row_values[i]);
            tableData.push_back(getValue(_row_values[i], col_value));
        }

        return Table<ROW_TYPE,VAL_TYPE>(keyValues, tableData);
    }

    /**
     * \brief Returns table value for the given keys.
     *
     * Returns table value for the given keys values using bilinear
     * interpolation algorithm.
     *
     * \param rowValue row key value
     * \param colValue column key value
     * \return interpolated value on success or NaN on failure
     */
    VAL_TYPE getValue(ROW_TYPE row_value, COL_TYPE col_value) const
    {
        if (_size > 0)
        {
            if (row_value < _row_values[0])
                return getValue(_row_values[0], col_value);

            if (col_value < _col_values[0])
                return getValue(row_value, _col_values[0]);

            if (row_value > _row_values[_rows - 1])
                return getValue(_row_values[_rows - 1], col_value);

            if (col_value > _col_values[_cols - 1])
                return getValue(row_value, _col_values[_cols - 1]);

            unsigned int row_1 = 0;
            unsigned int row_2 = 0;

            for (unsigned int r = 1; r < _rows; ++r)
            {
                row_1 = r - 1;
                row_2 = r;

                if (row_value >= _row_values[row_1] && row_value < _row_values[row_2]) break;
            }

            unsigned int col_1 = 0;
            unsigned int col_2 = 0;

            for (unsigned int c = 1; c < _cols; ++c)
            {
                col_1 = c - 1;
                col_2 = c;

                if (col_value >= _col_values[col_1] && col_value < _col_values[col_2]) break;
            }

            VAL_TYPE result_1 = static_cast<double>(col_value - _col_values[col_1])
                            * _inter_data[row_1 * _cols + col_1]
                            + _table_data[row_1 * _cols + col_1];

            VAL_TYPE result_2 = static_cast<double>(col_value - _col_values[col_1])
                            * _inter_data[row_2 * _cols + col_1]
                            + _table_data[row_2 * _cols + col_1];

            double rowFactor = 0.0;
            double rowDelta  = static_cast<double>(_row_values[row_2] - _row_values[row_1]);
            if (fabs(rowDelta) > 1.0e-16)
            {
                rowFactor = (row_value - _row_values[row_1]) / rowDelta;
            }

            return rowFactor * (result_2 - result_1) + result_1;
        }

        return VAL_TYPE{ std::numeric_limits<double>::quiet_NaN() };
    }

    /**
     * \brief Returns table value for the given key index.
     * \param rowIndex row index
     * \param colIndex col index
     * \return value on success or NaN on failure
     */
    VAL_TYPE getValueByIndex(unsigned int row_index, unsigned int col_index) const
    {
        if (_rows > 0 && row_index < _rows
         && _cols > 0 && col_index < _cols)
        {
            return _table_data[row_index * _cols + col_index];
        }

        return VAL_TYPE{ std::numeric_limits<double>::quiet_NaN() };
    }

    /**
     * \brief Checks if table is valid.
     * \return returns true if size is greater than 0 and all data is valid
     */
    bool isValid() const
    {
        bool result = (_size > 0) ? true : false;

        if (result)
        {
            for (unsigned int c = 0; c < _cols && result; ++c)
            {
                result &= mc::isValid(_col_values[c]);

                if (c > 0)
                {
                    result &= _col_values[c - 1] < _col_values[c];
                }
            }

            for (unsigned int r = 0; r < _rows && result; ++r)
            {
                result = mc::isValid(_row_values[r]);

                if (r > 0)
                {
                    result &= _row_values[r - 1] < _row_values[r];
                }
            }

            for (unsigned int i = 0; i < _size && result; ++i)
            {
                result &= mc::isValid(_table_data[i]);
                result &= mc::isValid(_inter_data[i]);
            }
        }

        return result;
    }

    /**
     * \brief Multiplies rows values by the given factor.
     * \param factor given factor
     */
    void multiplyRows(double factor)
    {
        for (unsigned int i = 0; i < _rows; ++i)
        {
            _row_values[i] *= factor;
        }

        updateInterpolationData();
    }

    /**
     * \brief Multiplies columns values by the given factor.
     * \param factor given factor
     */
    void multiplyCols(double factor)
    {
        for (unsigned int i = 0; i < _cols; ++i)
        {
            _col_values[i] *= factor;
        }

        updateInterpolationData();
    }

    /**
     * \brief Multiplies values by the given factor.
     * \param factor given factor
     */
    void multiplyValues(double factor)
    {
        for (unsigned int i = 0; i < _size; ++i)
        {
            _table_data[i] *= factor;
        }

        updateInterpolationData();
    }

    /**
     * \brief Sets table data.
     *
     * This constructor is used to initialize table with data.
     * Table data index should match following scheme i = i_row * no_of_columns + i_col
     *
     * \param row_values rows key values ordered vector
     * \param col_values columns key values ordered vector
     * \param table_data table values ordered vector
     */
    void setData(const std::vector<ROW_TYPE>& row_values,
                 const std::vector<COL_TYPE>& col_values,
                 const std::vector<VAL_TYPE>& table_data)
    {
        deleteArrays();

        if (row_values.size() * col_values.size() == table_data.size())
        {
            _size = static_cast< unsigned int >( table_data.size() );

            if (_size > 0)
            {
                _rows = static_cast<unsigned int>(row_values.size());
                _cols = static_cast<unsigned int>(col_values.size());

                createArrays();

                for (unsigned int i = 0; i < _rows; ++i) _row_values[i] = row_values[i];
                for (unsigned int i = 0; i < _cols; ++i) _col_values[i] = col_values[i];

                for (unsigned int i = 0; i < _size; ++i)
                {
                    _table_data[i] = table_data[i];
                    _inter_data[i] = 0.0;
                }

                updateInterpolationData();
            }
        }
    }

    /**
     * \brief Sets table data from string.
     *
     * Values in the given string should be separated with whitespaces.
     *
     * \param str given string
     */
    void setFromString(const char* str)
    {
        std::vector<ROW_TYPE> row_values_tmp;
        std::vector<COL_TYPE> col_values_tmp;
        std::vector<VAL_TYPE> table_data_tmp;

        std::stringstream ss(misc::stripSpaces(str));
        std::stringstream sl(misc::getFirstLine(ss.str()));

        bool valid = true;

        // cols keys
        while (!sl.eof() && valid)
        {
            double key = std::numeric_limits<double>::quiet_NaN();
            sl >> key; // sic!
            ss >> key; // sic!
            valid &= mc::isValid(key);
            col_values_tmp.push_back(COL_TYPE{key});
        }

        // table rows
        while (!ss.eof() && valid)
        {
            double key = std::numeric_limits<double>::quiet_NaN();
            ss >> key;
            valid &= mc::isValid(key);
            row_values_tmp.push_back(ROW_TYPE{key});

            // table data
            for (unsigned int i = 0; i < col_values_tmp.size(); i++)
            {
                double val = std::numeric_limits<double>::quiet_NaN();
                ss >> val;
                valid &= mc::isValid(val);
                table_data_tmp.push_back(VAL_TYPE{val});
            }
        }

        std::vector<ROW_TYPE> row_values { ROW_TYPE{std::numeric_limits<double>::quiet_NaN()} };
        std::vector<COL_TYPE> col_values { COL_TYPE{std::numeric_limits<double>::quiet_NaN()} };
        std::vector<VAL_TYPE> table_data { VAL_TYPE{std::numeric_limits<double>::quiet_NaN()} };

        if (valid)
        {
            row_values = row_values_tmp;
            col_values = col_values_tmp;
            table_data = table_data_tmp;
        }

        setData(row_values, col_values, table_data);
    }

    /**
     * \brief Returns string representation of the table.
     */
    std::string toString()
    {
        std::stringstream ss;

        ss << "\t";

        for (unsigned int c = 0; c < _cols; ++c)
        {
            if (c > 0) ss << "\t";
            ss << static_cast<double>(_col_values[c]);
        }

        ss << std::endl;

        for (unsigned int r = 0; r < _rows; ++r)
        {
            ss << static_cast<double>(_row_values[r]);
            for (unsigned int c = 0; c < _cols; ++c)
            {
                ss << "\t" << static_cast<double>(_table_data[r * _cols + c]);
            }
            ss << std::endl;
        }

        return ss.str();
    }

    inline unsigned int rows() const { return _rows; }
    inline unsigned int cols() const { return _cols; }

    /** \brief Assignment operator. */
    Table2<ROW_TYPE,COL_TYPE,VAL_TYPE>& operator=(const Table2<ROW_TYPE,COL_TYPE,VAL_TYPE>& table)
    {
        if (this != &table)
        {
            deleteArrays();

            _rows = table._rows;
            _cols = table._cols;
            _size = table._size;

            if (_size > 0)
            {
                createArrays();

                for (unsigned int i = 0; i < _rows; ++i) _row_values[i] = table._row_values[i];
                for (unsigned int i = 0; i < _cols; ++i) _col_values[i] = table._col_values[i];

                for (unsigned int i = 0; i < _size; ++i)
                {
                    _table_data[i] = table._table_data[i];
                    _inter_data[i] = table._inter_data[i];
                }
            }
        }

        return *this;
    }

    /** \brief Move assignment operator. */
    Table2<ROW_TYPE,COL_TYPE,VAL_TYPE>& operator=(Table2<ROW_TYPE,COL_TYPE,VAL_TYPE>&& table)
    {
        deleteArrays();

        _rows = std::exchange(table._rows, 0);
        _cols = std::exchange(table._cols, 0);
        _size = std::exchange(table._size, 0);

        _row_values = std::exchange(table._row_values, nullptr);
        _col_values = std::exchange(table._col_values, nullptr);
        _table_data = std::exchange(table._table_data, nullptr);

        _inter_data = std::exchange(table._inter_data, nullptr);

        return *this;
    }

private:

    unsigned int _rows = 0;               ///< number of rows
    unsigned int _cols = 0;               ///< number of columns
    unsigned int _size = 0;               ///< number of table elements

    ROW_TYPE* _row_values = nullptr;      ///< rows keys values
    COL_TYPE* _col_values = nullptr;      ///< columns keys values
    VAL_TYPE* _table_data = nullptr;      ///< table data
    double* _inter_data = nullptr;        ///< interpolation data matrix

    /** Creates data tables. */
    void createArrays()
    {
        _row_values = new ROW_TYPE [_rows];
        _col_values = new COL_TYPE [_cols];
        _table_data = new VAL_TYPE [_size];
        _inter_data = new double [_size];
    }

    /** Deletes data tables. */
    void deleteArrays()
    {
        if ( _row_values ) { delete[] _row_values; } _row_values = nullptr;
        if ( _col_values ) { delete[] _col_values; } _col_values = nullptr;
        if ( _table_data ) { delete[] _table_data; } _table_data = nullptr;
        if ( _inter_data ) { delete[] _inter_data; } _inter_data = nullptr;
    }

    /** \brief Updates interpolation data due to table data. */
    void updateInterpolationData()
    {
        for (unsigned int r = 0; r < _rows; ++r)
        {
            for (unsigned int c = 0; c < _cols - 1; ++c)
            {
                _inter_data[r * _cols + c] =
                    static_cast<double>(_table_data[r * _cols + c + 1] - _table_data[r * _cols + c])
                  / static_cast<double>(_col_values[c + 1] - _col_values[c]);
            }
        }
    }
};

} // namespace mc

#endif // MCUTILS_MATH_TABLE2_H_
