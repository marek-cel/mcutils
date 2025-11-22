/****************************************************************************//*
 * Copyright (C) 2025 Marek M. Cel
 ******************************************************************************/
#ifndef MCSIM_EXTRA_UNITS_H_
#define MCSIM_EXTRA_UNITS_H_

#include <units.h>

namespace units {

	//------------------------------
	// AUXILIARY UNITS
	//------------------------------
#   if !defined(DISABLE_PREDEFINED_UNITS) || defined(ENABLE_PREDEFINED_AUXILIARY_UNITS)
	UNIT_ADD(auxiliary, per_meter          , per_meter          , per_m    , compound_unit<inverse<length::meter>>)
	UNIT_ADD(auxiliary, per_centimeter     , per_centimeter     , per_cm   , compound_unit<inverse<length::centimeter>>)
	UNIT_ADD(auxiliary, per_foot           , per_foot           , per_ft   , compound_unit<inverse<length::foot>>)
	UNIT_ADD(auxiliary, per_inch           , per_inch           , per_in   , compound_unit<inverse<length::inch>>)
	//UNIT_ADD(auxiliary, per_second         , per_second         , per_s    , unit<std::ratio<1>, frequency::hertz>)
	UNIT_ADD(auxiliary, per_second_squared , per_second_squared , per_s_sq , compound_unit<inverse<squared<time::second>>>)
	UNIT_ADD(auxiliary, per_radian         , per_radian         , per_rad  , compound_unit<inverse<angle::radian>>)
	UNIT_ADD(auxiliary, per_degree         , per_degree         , per_deg  , compound_unit<inverse<angle::degree>>)

	namespace auxiliary {
		using per_second_t = frequency::hertz_t;
	} // namespace auxiliary
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
		using per_radian_t = auxiliary::per_radian_t;
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

} // namespace units

#endif // MCSIM_EXTRA_UNITS_H_
