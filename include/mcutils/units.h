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
#ifndef MCUTILS_UNITS_H_
#define MCUTILS_UNITS_H_

#include <units.h>

namespace units {

	//------------------------------
	// INVERTED UNITS
	//------------------------------
#   if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_INVERTED_UNITS)
	UNIT_ADD(inverted, per_meter          , per_meter          , per_m    , compound_unit<inverse<length::meter>>)
	UNIT_ADD(inverted, per_centimeter     , per_centimeter     , per_cm   , compound_unit<inverse<length::centimeter>>)
	UNIT_ADD(inverted, per_foot           , per_foot           , per_ft   , compound_unit<inverse<length::foot>>)
	UNIT_ADD(inverted, per_inch           , per_inch           , per_in   , compound_unit<inverse<length::inch>>)
	UNIT_ADD(inverted, per_second_squared , per_second_squared , per_s_sq , compound_unit<inverse<squared<time::second>>>)
	UNIT_ADD(inverted, per_radian         , per_radian         , per_rad  , compound_unit<inverse<angle::radian>>)
	UNIT_ADD(inverted, per_degree         , per_degree         , per_deg  , compound_unit<inverse<angle::degree>>)

	namespace inverted
	{
		using per_second = compound_unit<inverse<time::second>>;
		using per_second_t = unit_t<per_second>;
	} // namespace inverted

	namespace literals
	{
		inline constexpr inverted::per_second_t operator""_per_s(long double val)
		{
			return inverted::per_second_t(static_cast<double>(val));
		}

		inline constexpr inverted::per_second_t operator""_per_s(unsigned long long val)
		{
			return inverted::per_second_t(static_cast<double>(val));
		}
	} // namespace literals
#   endif

	//------------------------------
	// MOMENT OF INERTIA UNITS
	//------------------------------
#   if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_MOMENT_OF_INERTIA_UNITS)
	UNIT_ADD(moment_of_inertia, kilograms_meters_squared, kilograms_meters_squared, kg_m_sq, compound_unit<mass::kilograms, squared<length::meters>>)
	UNIT_ADD(moment_of_inertia, slugs_feet_squared, slugs_feet_squared, slugs_ft_sq, compound_unit<mass::slugs, squared<length::feet>>)
#   endif

	//------------------------------
	// FIRST MOMENT OF MASS
	//------------------------------
#	if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_FIRST_MOMENT_OF_MASS_UNITS)
    UNIT_ADD(first_moment_of_mass, kilogram_meter, kilogram_meter, kg_m, compound_unit<mass::kilogram, length::meter>)
    UNIT_ADD(first_moment_of_mass, slug_feet, slug_feet, slug_ft, compound_unit<mass::slug, length::feet>)
#	endif

	//------------------------------
	// VELOCITY UNITS
	//------------------------------
#   if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_VELOCITY_UNITS)
	UNIT_ADD(velocity, feet_per_minute, feet_per_minute, fpm, compound_unit<length::feet, inverse<time::minutes>>)
#   endif

	//------------------------------
	// ANGULAR ACCELERATION UNITS
	//------------------------------
#   if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_ANGULAR_ACCELERATION_UNITS)
	UNIT_ADD(angular_acceleration, radians_per_second_squared, radians_per_second_squared, rad_per_s_sq, compound_unit<angle::radians, inverse<squared<time::seconds>>>)
	UNIT_ADD(angular_acceleration, degrees_per_second_squared, degrees_per_second_squared, deg_per_s_sq, compound_unit<angle::degrees, inverse<squared<time::seconds>>>)
#   endif

	//------------------------------
	// PRESSURE UNITS
	//------------------------------
#	if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_PRESSURE_UNITS)
    UNIT_ADD(pressure, pounds_per_square_foot, pounds_per_square_foot, psf, compound_unit<force::pounds, inverse<squared<length::foot>>>)
#	endif

	//------------------------------
	// STANDARD GRAVITATIONAL PARAMETER UNITS
	//------------------------------
#   if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_STANDARD_GRAVITATIONAL_PARAMETER_UNITS)
	UNIT_ADD(standard_gravitational_parameter, cubic_meters_per_second_squared, cubic_meters_per_second_squared, cu_m_per_s_sq, compound_unit<cubed<length::meter>, inverse<squared<time::second>>>)
#   endif

	//------------------------------
	// STIFFNESS UNITS
	//------------------------------
#   if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_STIFFNESS_UNITS)
	UNIT_ADD(stiffness, newtons_per_meter, newtons_per_meter, N_per_m, compound_unit<force::newton, inverse<length::meter>>)
	UNIT_ADD(stiffness, pounds_per_foot, pounds_per_foot, lbf_per_ft, compound_unit<force::pound, inverse<length::foot>>)
#   endif

	//------------------------------
	// VISCOUS DAMPING UNITS
	//------------------------------
#   if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_VISCOUS_DAMPING_UNITS)
	UNIT_ADD(viscous_damping, newtons_per_meters_per_second, newtons_per_meters_per_second, N_per_mps, compound_unit<force::newton, time::second, inverse<length::meter>>)
	UNIT_ADD(viscous_damping, pounds_per_feet_per_second, pounds_per_feet_per_second, lbf_per_fps, compound_unit<force::pound, time::second, inverse<length::foot>>)
#   endif

	//------------------------------
	// AERODYNAMIC DERIVATIVES UNITS
	//------------------------------
#   if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_AERODYNAMIC_DERIVATIVES_UNITS)
	namespace aero_derivative {
		using per_degree = compound_unit<inverse<angle::degree>>;
		using per_degree_t = inverted::per_degree_t;
		using per_radian = compound_unit<inverse<angle::radian>>;
		using per_radian_t = inverted::per_radian_t;
	}
#   endif

	//------------------------------
	// TEMPERATURE GRADIENT
	//------------------------------
#	if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_TEMPERATURE_GRADIENT_UNITS)
	UNIT_ADD(temperature_gradient, kelvins_per_meter, kelvins_per_meter, K_per_m, compound_unit<temperature::kelvin, inverse<length::meter>>)
    UNIT_ADD(temperature_gradient, kelvins_per_kilometer, kelvins_per_kilometer, K_per_km, compound_unit<temperature::kelvin, inverse<length::kilometer>>)
#	endif

	//------------------------------
	// MOLAR MASS
	//------------------------------
#	if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_MOLAR_MASS_UNITS)
	UNIT_ADD(molar_mass, kilograms_per_mole, kilograms_per_mole, kg_per_mol, compound_unit<mass::kilogram, inverse<substance::mole>>)
#	endif

	//------------------------------
	// DYNAMIC VISCOSITY
	//------------------------------
#	if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_DYNAMIC_VISCOSITY_UNITS)
	UNIT_ADD(dynamic_viscosity, pascal_second, pascal_second, Pa_s, compound_unit<mass::kilogram, inverse<compound_unit<length::meter, time::second>>>)
#	endif

	//------------------------------
	// KINEMATIC VISCOSITY
	//------------------------------
#	if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_KINEMATIC_VISCOSITY_UNITS)
	UNIT_ADD(kinematic_viscosity, meters_squared_per_second, meters_squared_per_second, m_sq_per_s, compound_unit<squared<length::meter>, inverse<time::second>>)
#	endif

	//------------------------------
	// GAS CONSTANT
	//------------------------------
#	if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_GAS_CONSTANT_UNITS)
	UNIT_ADD(gas_constant, joules_per_kelvin_per_mole, joules_per_kelvin_per_mole, J_per_K_per_mol, compound_unit<energy::joules, inverse<temperature::kelvin>, inverse<substance::moles>>)
#	endif

	namespace traits {

		/**
		 * \brief trait to detect if a unit_t has an angle dimension.
		 */
		template<typename T>
		struct has_angle_dimension_t : std::false_type {};

		/**
		 * \brief specialization for unit_t types to detect if they have an angle dimension.
		 */
		template<typename T>
		requires is_unit_t<T>::value
		struct has_angle_dimension_t<T> 
		{
			using base = typename T::unit_type::base_unit_type;
			static constexpr bool value = !std::is_same_v<typename base::radian_ratio, std::ratio<0>>;
		};

		template<typename LHS, typename RHS>
		struct need_angle_stripping : std::false_type {};

		template<typename LHS, typename RHS>
		requires (
			traits::is_unit_t<LHS>::value &&
			traits::is_unit_t<RHS>::value &&
			units::traits::is_convertible_unit_t<LHS, RHS>::value == false &&
			units::traits::is_convertible_unit_t<LHS, units::time::second_t>::value == false &&
			units::traits::is_convertible_unit_t<RHS, units::time::second_t>::value == false &&
			(traits::has_angle_dimension_t<LHS>::value != traits::has_angle_dimension_t<RHS>::value)
		)
		struct need_angle_stripping<LHS, RHS> : std::true_type {};

	} // namespace traits

	namespace detail {
		
		/**
		 * \brief Metafunction to strip the angle dimension from a unit_t type.
		 */
		template<typename T>
		requires traits::has_angle_dimension_t<T>::value
		struct strip_angle_dimension
		{
			using si_base = typename T::unit_type::base_unit_type;
			using si_unit = units::unit<std::ratio<1>, si_base>;
			using si_type = units::unit_t<si_unit, typename T::underlying_type>;

			using stripped_si_base = units::base_unit<
				typename si_base::meter_ratio,
				typename si_base::kilogram_ratio,
				typename si_base::second_ratio,
				std::ratio<0>, // Radian removed
				typename si_base::ampere_ratio,
				typename si_base::kelvin_ratio,
				typename si_base::mole_ratio,
				typename si_base::candela_ratio,
				typename si_base::byte_ratio
			>;
			
			using stripped_si_unit = unit<std::ratio<1>, stripped_si_base>;

			using type = unit_t<stripped_si_unit, typename T::underlying_type>;

			/**
			 * \brief Function to strip the angle dimension from a unit_t instance.
			 * \param value The unit_t instance to strip.
			 * \return A new unit_t instance without the angle dimension.
			 */
			static constexpr type strip(const T& value) noexcept
			{
				si_type si_val = value;
				return type(si_val());
			}
		};

	} // namespace detail

} // namespace units

#endif // MCUTILS_UNITS_H_
