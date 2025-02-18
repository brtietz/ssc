/**
BSD-3-Clause
Copyright 2019 Alliance for Sustainable Energy, LLC
Redistribution and use in source and binary forms, with or without modification, are permitted provided
that the following conditions are met :
1.	Redistributions of source code must retain the above copyright notice, this list of conditions
and the following disclaimer.
2.	Redistributions in binary form must reproduce the above copyright notice, this list of conditions
and the following disclaimer in the documentation and/or other materials provided with the distribution.
3.	Neither the name of the copyright holder nor the names of its contributors may be used to endorse
or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER, CONTRIBUTORS, UNITED STATES GOVERNMENT OR UNITED STATES
DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef SYSTEM_ADVISOR_MODEL_CMOD_PVSAMV1_EQNS_H
#define SYSTEM_ADVISOR_MODEL_CMOD_PVSAMV1_EQNS_H

#include "sscapi.h"

#ifdef __cplusplus
extern "C" {
#endif

static const char *Reopt_size_battery_params_doc =
        "Given a PV system, get the optimal battery size. Wind and additional PV are disabled.\\n"
        "Maps SAM compute module inputs to those of the ReOpt Lite API:\\n"
        "Pvsamv1 or Pvwattsv5 technology paired with Residential, Commercial, Third Party or Host Developer financing.\\n\\n"
        "Optional: if missing, variable will be set to default value if documented, to REopt defaults otherwise.\\n"
        "Conditional: only required if the variable it's meant to replace is missing.\\n"
        "REopt's 'microgrid_upgrade_cost_pct' set to 0 because SAM doesn't apply this cost multiplier.\\n"
        "REopt inputs not used in this function will be REopt's defaults.\\n\\n"
        "Input: var_table with key-value pairs:  \\n"
        "     ++ Site inputs ++\\n"
        "         'lon': double, longitude\\n"
        "         'lat': double, latitude\\n"
        "     ++ PV inputs ++\\n"
        "         'array_type': double, 0=FixedGround,1=FixedRoof,2=1Axis,3=Backtracked,4=2Axis, can be replaced by (subarray1_track_mode, subarray1_backtrack)\\n"
	    "         'module_type': optional double, 0=Standard,1=Premium,2=Thin Film. Default is 1\\n"
        "         'subarray1_track_mode': conditional double, 0=fixed,1=1axis,2=2axis,3=azi,4=monthly, replaces array_type\\n"
        "         'subarray1_backtrack': conditional double, 0=false, 1=true, replaces array_type\\n"
        "         'azimuth': double, can be replaced by subarray1_azimuth\\n"
        "         'subarray1_azimuth': conditional double\\n"
        "         'tilt': double, can be replaced by subarray1_tilt\\n"
        "         'subarray1_tilt': conditional double\\n"
        "         'gcr': double, can be replaced by subarray1_gcr\\n"
        "         'subarray1_gcr': conditional double, ground coverage ratio, between 0 and 1\\n"
        "         'inv_eff': double, can be replaced by (inverter_model, oneof(inv_snl_eff_cec, inv_ds_eff, inv_pd_eff, inv_cec_cg_eff))\\n"
        "         'inverter_model': conditional double, 0=cec,1=datasheet,2=partload,3=coefficientgenerator\\n"
        "         oneof(inv_snl_eff_cec, inv_ds_eff, inv_pd_eff, inv_cec_cg_eff) - conditional double [%], inverter efficiency for selected inverter model, 0-100\\n"
        "         'dc_ac_ratio': double, can be replaced by (inverter_model, oneof(inv_snl_paco, inv_ds_paco, inv_pd_paco, inv_cec_cg_paco), inverter_count)\\n"
        "         oneof(inv_snl_paco, inv_ds_paco, inv_pd_paco, inv_cec_cg_paco) - conditional double [Wac], inverter AC maximum power rating for selected inverter model\\n"
        "         'inverter_count': conditional double\\n"
        "         'losses': double [%], Total system power loss, 0-100, can be replaced by annual_total_loss_percent\\n"
        "         'annual_total_loss_percent': conditional double [%], Total system power loss, 0-100.\\n"
        "         'system_capacity': double [kW], PV AC system size\\n"
        "         'degradation': optional double [%/year], Annual PV energy production degradation, 0-100. Default is 0.5\\n"
        "         'om_fixed': optional double [$/year], Fixed O&M annual amount. Default is 0\\n"
        "         'om_production': optional double [$/MWh], Production-based O&M amount. Default is 0\\n"
        "         'total_installed_cost': optional double [$], Total system installation cost\\n"
        "         'itc_fed_percent': optional double [%], Percentage of capital costs that are credited towards federal taxes, 0-100. Default is 0\\n"
        "         'pbi_fed_amount': optional double [$/kWh], Federal PBI amount. Default is 0\\n"
        "         'pbi_fed_term': optional double [years], Federal PBI term. Double is 0\\n"
        "         'ibi_sta_percent': optional double [%], Federal percentage-based IBI percent, 0-100. Default is 0\\n"
        "         'ibi_sta_percent_maxvalue': optional double [$], Federal percentage-based IBI maximum value.\\n"
        "         'ibi_uti_percent': optional double [%], Utility percentage-based IBI percent, 0-100. Default is 0\\n"
        "         'ibi_uti_percent_maxvalue': optional double [$], Utility percentage-based IBI maximum value\\n"
        "         'depr_bonus_fed': optional double [%], Percent of upfront project costs to depreciate in year one in addition to scheduled depreciation, 0-100\\n"
        "         'depr_bonus_fed_macrs_5': optional double [0/1], Federal bonus depreciation follows 5-yr MACRS\\n"
        "     ++ Battery inputs ++\\n"
        "         'batt_dc_ac_efficiency': optional double [%], Battery DC to AC efficiency, 0-100\\n"
        "         'batt_ac_dc_efficiency': optional double [%], Inverter AC to battery DC efficiency, 0-100\\n"
        "         'battery_per_kW': optional double [$/kW], Battery cost per kW\\n"
        "         'battery_per_kWh': optional double [$/kWh], Battery cost per kWh\\n"
        "         'batt_initial_SOC': optional double [%], Initial State-of-Charge, 0-100\\n"
        "         'batt_minimum_SOC': optional double [%], Minimum State-of-Charge, 0-100. Default is 20.\\n"
        "         'batt_replacement_schedule_percent': optional array [%], Percentage in each year from start of analysis period to replace battery. Default is [0]\\n"
        "         'om_batt_replacement_cost': optional double [$/kWh], Cost to replace battery per kWh\\n"
        "     ++ Utility Rate inputs ++\\n"
        "         'ur_monthly_fixed_charge': double [$], Monthly fixed charge\\n"
        "         'ur_dc_sched_weekday': matrix [tiers], Demand charge weekday schedule, count starts at 1, 12mx24hr\\n"
        "         'ur_dc_sched_weekend': matrix [tiers], Demand charge weekend schedule, count starts at 1, 12mx24hr\\n"
        "         'ur_dc_tou_mat': matrix [[period, tier, kWh, 'kWh', $/kWh], Energy rates (TOU), each row provides period, tier, max usage, 'kWh' units, and charge\\n"
        "         'ur_dc_flat_mat' -matrix [[month, tier, kW, $]] - Demand rates (flat), each row provides month, tier, peak demand and charge \\n"
        "         'ur_ec_sched_weekday': matrix [tiers], Energy charge weekday schedule, count starts at 1, 12mx24hr\\n"
        "         'ur_ec_sched_weekend': matrix [tiers], Energy charge weekend schedule, count starts at 1, 12mx24hr\\n"
        "         'ur_ec_tou_mat': matrix [[period, tier, kw, $], Demand rates (TOU), each row provides period, tier, peak power, and charge\\n"
        "         'load': array [kW], Electricity load (year 1)\\n"
        "         'crit_load': optional array [kW], Critical electricity load (year 1)\\n"
        "     ++ Financial inputs ++\\n"
        "         'analysis_period': double [years]\\n"
        "         'rate_escalation': double [%/year], Annual electricity rate escalation, 0-100\\n"
        "         'inflation_rate': double [%], 0-100\\n"
        "         'federal_tax_rate': optional double [%], Used to calculate offtaker tax percent, 0-100\\n"
        "         'state_tax_rate': optional double [%], Used to calculate offtaker tax percent, 0-100\\n"
        "         'real_discount_rate': optional double [%], 0-100. Default is 6.4\\n"
        "         'om_fixed_escal': optional double [%/year], Fixed O&M escalation\\n"
        "         'om_production_escal': optional double [%/year], Production-based O&M escalation\\n"
        "         'total_installed_cost': optional double [$]\\n"
        "         'value_of_lost_load': optional double [$/kWh], Value placed on unmet site load during grid outages\\n\\n"
        "Output: key-value pairs added to var_table\\n"
        "         'reopt_scenario': table, Scenario inputs to Reopt Lite API\\n"
        "         'log': string";

SSCEXPORT bool Reopt_size_battery_params(ssc_data_t data);


}

#endif //SYSTEM_ADVISOR_MODEL_CMOD_PVSAMV1_EQNS_H
