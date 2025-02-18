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

#include "cmod_financial_eqns.h"
#include "common_financial.h"
#include "vartab.h"

#pragma warning(disable: 4297)  // ignore warning: 'function assumed not to throw an exception but does'

bool Financial_Construction_Financing_Equations(ssc_data_t data)
{
    auto vt = static_cast<var_table*>(data);
    if (!vt) {
        return false;
    }
    double total_installed_cost,
        const_per_percent1, const_per_principal1,
        const_per_interest1, const_per_interest_rate1, const_per_months1,
        const_per_upfront_rate1, const_per_total1,
        const_per_percent2, const_per_principal2,
        const_per_interest2, const_per_interest_rate2, const_per_months2,
        const_per_upfront_rate2, const_per_total2,
        const_per_percent3, const_per_principal3,
        const_per_interest3, const_per_interest_rate3, const_per_months3,
        const_per_upfront_rate3, const_per_total3,
        const_per_percent4, const_per_principal4,
        const_per_interest4, const_per_interest_rate4, const_per_months4,
        const_per_upfront_rate4, const_per_total4,
        const_per_percent5, const_per_principal5,
        const_per_interest5, const_per_interest_rate5, const_per_months5,
        const_per_upfront_rate5, const_per_total5,
        const_per_principal_total, const_per_percent_total, construction_financing_cost, const_per_interest_total;

    vt_get_number(vt, "total_installed_cost", &total_installed_cost);

    // Loan 1
    vt_get_number(vt, "const_per_interest_rate1", &const_per_interest_rate1);
    vt_get_number(vt, "const_per_months1", &const_per_months1);
    vt_get_number(vt, "const_per_percent1", &const_per_percent1);
    vt_get_number(vt, "const_per_upfront_rate1", &const_per_upfront_rate1);
    const_per_principal1 = Const_per_principal(const_per_percent1, total_installed_cost);
    const_per_interest1 = Const_per_interest(const_per_principal1, const_per_interest_rate1, const_per_months1);
    const_per_total1 = Const_per_total(const_per_interest1, const_per_principal1, const_per_upfront_rate1);
    vt->assign("const_per_principal1", const_per_principal1);
    vt->assign("const_per_interest1", const_per_interest1);
    vt->assign("const_per_total1", const_per_total1);

    // Loan 2
    vt_get_number(vt, "const_per_interest_rate2", &const_per_interest_rate2);
    vt_get_number(vt, "const_per_months2", &const_per_months2);
    vt_get_number(vt, "const_per_percent2", &const_per_percent2);
    vt_get_number(vt, "const_per_upfront_rate2", &const_per_upfront_rate2);
    const_per_principal2 = Const_per_principal(const_per_percent2, total_installed_cost);
    const_per_interest2 = Const_per_interest(const_per_principal2, const_per_interest_rate2, const_per_months2);
    const_per_total2 = Const_per_total(const_per_interest2, const_per_principal2, const_per_upfront_rate2);
    vt->assign("const_per_principal2", const_per_principal2);
    vt->assign("const_per_interest2", const_per_interest2);
    vt->assign("const_per_total2", const_per_total2);

    // Loan 3
    vt_get_number(vt, "const_per_interest_rate3", &const_per_interest_rate3);
    vt_get_number(vt, "const_per_months3", &const_per_months3);
    vt_get_number(vt, "const_per_percent3", &const_per_percent3);
    vt_get_number(vt, "const_per_upfront_rate3", &const_per_upfront_rate3);
    const_per_principal3 = Const_per_principal(const_per_percent3, total_installed_cost);
    const_per_interest3 = Const_per_interest(const_per_principal3, const_per_interest_rate3, const_per_months3);
    const_per_total3 = Const_per_total(const_per_interest3, const_per_principal3, const_per_upfront_rate3);
    vt->assign("const_per_principal3", const_per_principal3);
    vt->assign("const_per_interest3", const_per_interest3);
    vt->assign("const_per_total3", const_per_total3);

    // Loan 4
    vt_get_number(vt, "const_per_interest_rate4", &const_per_interest_rate4);
    vt_get_number(vt, "const_per_months4", &const_per_months4);
    vt_get_number(vt, "const_per_percent4", &const_per_percent4);
    vt_get_number(vt, "const_per_upfront_rate4", &const_per_upfront_rate4);
    const_per_principal4 = Const_per_principal(const_per_percent4, total_installed_cost);
    const_per_interest4 = Const_per_interest(const_per_principal4, const_per_interest_rate4, const_per_months4);
    const_per_total4 = Const_per_total(const_per_interest4, const_per_principal4, const_per_upfront_rate4);
    vt->assign("const_per_principal4", const_per_principal4);
    vt->assign("const_per_interest4", const_per_interest4);
    vt->assign("const_per_total4", const_per_total4);

    // Loan 5
    vt_get_number(vt, "const_per_interest_rate5", &const_per_interest_rate5);
    vt_get_number(vt, "const_per_months5", &const_per_months5);
    vt_get_number(vt, "const_per_percent5", &const_per_percent5);
    vt_get_number(vt, "const_per_upfront_rate5", &const_per_upfront_rate5);
    const_per_principal5 = Const_per_principal(const_per_percent5, total_installed_cost);
    const_per_interest5 = Const_per_interest(const_per_principal5, const_per_interest_rate5, const_per_months5);
    const_per_total5 = Const_per_total(const_per_interest5, const_per_principal5, const_per_upfront_rate5);
    vt->assign("const_per_principal5", const_per_principal5);
    vt->assign("const_per_interest5", const_per_interest5);
    vt->assign("const_per_total5", const_per_total5);


    const_per_principal_total = const_per_principal1 + const_per_principal2 + const_per_principal3 + const_per_principal4 + const_per_principal5;
    const_per_percent_total = const_per_percent1 + const_per_percent2 + const_per_percent3 + const_per_percent4 + const_per_percent5;
    construction_financing_cost = const_per_total1 + const_per_total2 + const_per_total3 + const_per_total4 + const_per_total5;
    const_per_interest_total = const_per_interest1 + const_per_interest2 + const_per_interest3 + const_per_interest4 + const_per_interest5;
    vt->assign("const_per_principal_total", const_per_principal_total);
    vt->assign("const_per_percent_total", const_per_percent_total);
    vt->assign("construction_financing_cost", construction_financing_cost);
    vt->assign("const_per_interest_total", const_per_interest_total);
    return true;
}

bool Financial_Capacity_Payments_Equations(ssc_data_t data)
{
    auto vt = static_cast<var_table*>(data);
    if (!vt) {
        return false;
    }

    double system_capacity, cp_system_nameplate;
    vt_get_number(vt, "system_capacity", &system_capacity);
    cp_system_nameplate = system_capacity / 1000.;
    vt->assign("cp_system_nameplate", cp_system_nameplate);
    return true;
}
