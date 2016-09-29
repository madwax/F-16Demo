// Source Data:
// 1) F-16 University of Minnesota Non-Linear Flight Model
//	  http://www.aem.umn.edu/people/faculty/balas/darpa_sec/SEC.Software.html
// 2) NASA TP 1538 Simulator Study of Stall/Post-Stall Characteristics of a 
//	  Fighter Airplane With Relaxed Longitudinal Static Stability

#ifndef _F16AERO_H_
#define _F16AERO_H_

#include <cmath>

#include "F16Constants.h"
#include "F16AeroData.h"
#include "F16AeroFunction.h"

#include "UtilityFunctions.h"

#include "FlightControls/F16FcsCommon.h"

#include "Atmosphere/F16Atmosphere.h"
#include "Atmosphere/F16GroundSurface.h"

// just container for results:
// keep in one place and reduce some repeated things
class F16AeroResults
{
public:
	double fn_Cx = 0.0;
	double fn_CxEle0 = 0.0;
	double fn_Cz = 0.0;
	double fn_CzEle0 = 0.0;
	double fn_Cm = 0.0;
	double fn_CmEle0 = 0.0;
	double fn_Cy = 0.0;
	double fn_Cn = 0.0;
	double fn_CnEle0 = 0.0;
	double fn_Cl = 0.0;
	double fn_ClEle0 = 0.0;
	double fn_Cx_lef = 0.0;
	double fn_Cz_lef = 0.0;
	double fn_Cm_lef = 0.0;
	double fn_Cy_lef = 0.0;
	double fn_Cn_lef = 0.0;
	double fn_Cl_lef = 0.0;
	double fn_CXq = 0.0;
	double fn_CZq = 0.0;
	double fn_CMq = 0.0;
	double fn_CYp = 0.0;
	double fn_CYr = 0.0;
	double fn_CNr = 0.0;
	double fn_CNp = 0.0;
	double fn_CLp = 0.0;
	double fn_CLr = 0.0;
	double fn_delta_CXq_lef = 0.0;
	double fn_delta_CYr_lef = 0.0;
	double fn_delta_CYp_lef = 0.0;
	double fn_delta_CZq_lef = 0.0;
	double fn_delta_CLr_lef = 0.0;
	double fn_delta_CLp_lef = 0.0;
	double fn_delta_CMq_lef = 0.0;
	double fn_delta_CNr_lef = 0.0;
	double fn_delta_CNp_lef = 0.0;
	double fn_Cy_r30 = 0.0;
	double fn_Cn_r30 = 0.0;
	double fn_Cl_r30 = 0.0;
	double fn_Cy_a20 = 0.0;
	double fn_Cy_a20_lef = 0.0;
	double fn_Cn_a20 = 0.0;
	double fn_Cn_a20_lef = 0.0;
	double fn_Cl_a20 = 0.0;
	double fn_Cl_a20_lef = 0.0;
	double fn_delta_CNbeta = 0.0;
	double fn_delta_CLbeta = 0.0;
	double fn_delta_Cm = 0.0;
	double fn_eta_el = 0.0;
public:
	F16AeroResults() {}
	~F16AeroResults() {}
};


class F16Aero
{
protected:
	F16Atmosphere *pAtmos;
	F16GroundSurface *pGrounds;

	double		m_Cx_total;
	double		m_Cz_total;
	double		m_Cm_total;
	double		m_Cy_total;
	double		m_Cn_total;
	double		m_Cl_total;

	F16AeroResults res;

	AERO_Function fn_Cx;
	AERO_Function fn_CxEle0;
	AERO_Function fn_Cz;
	AERO_Function fn_CzEle0;
	AERO_Function fn_Cm;
	AERO_Function fn_CmEle0;
	AERO_Function fn_Cy;
	AERO_Function fn_Cn;
	AERO_Function fn_CnEle0;
	AERO_Function fn_Cl;
	AERO_Function fn_ClEle0;
	AERO_Function fn_Cx_lef;
	AERO_Function fn_Cz_lef;
	AERO_Function fn_Cm_lef;
	AERO_Function fn_Cy_lef;
	AERO_Function fn_Cn_lef;
	AERO_Function fn_Cl_lef;
	AERO_Function fn_CXq;
	AERO_Function fn_CZq;
	AERO_Function fn_CMq;
	AERO_Function fn_CYp;
	AERO_Function fn_CYr;
	AERO_Function fn_CNr;
	AERO_Function fn_CNp;
	AERO_Function fn_CLp;
	AERO_Function fn_CLr;
	AERO_Function fn_delta_CXq_lef;
	AERO_Function fn_delta_CYr_lef;
	AERO_Function fn_delta_CYp_lef;
	AERO_Function fn_delta_CZq_lef;
	AERO_Function fn_delta_CLr_lef;
	AERO_Function fn_delta_CLp_lef;
	AERO_Function fn_delta_CMq_lef;
	AERO_Function fn_delta_CNr_lef;
	AERO_Function fn_delta_CNp_lef;
	AERO_Function fn_Cy_r30;
	AERO_Function fn_Cn_r30;
	AERO_Function fn_Cl_r30;
	AERO_Function fn_Cy_a20;
	AERO_Function fn_Cy_a20_lef;
	AERO_Function fn_Cn_a20;
	AERO_Function fn_Cn_a20_lef;
	AERO_Function fn_Cl_a20;
	AERO_Function fn_Cl_a20_lef;
	AERO_Function fn_delta_CNbeta;
	AERO_Function fn_delta_CLbeta;
	AERO_Function fn_delta_Cm;
	AERO_Function fn_eta_el;

	LinearFunction<double> cgLiftDiff;

	double m_CyAileronLeft;
	double m_CnAileronLeft;
	double m_ClAileronLeft;
	double m_CyAileronRight;
	double m_CnAileronRight;
	double m_ClAileronRight;

	double m_CyRudder;
	double m_CnRudder;
	double m_ClRudder;
	double m_CxFlapLeft;
	double m_CxFlapRight;
	double m_CzFlapLeft;
	double m_CzFlapRight;
	double m_CxAirbrake;
	double m_diffCgPCT;

public:
	F16Aero(F16Atmosphere *atmos, F16GroundSurface *grounds) :
		pAtmos(atmos),
		pGrounds(grounds),
		m_Cx_total(0),
		m_Cz_total(0),
		m_Cm_total(0),
		m_Cy_total(0),
		m_Cn_total(0),
		m_Cl_total(0),
		res(),
		fn_Cx(3, F16::_CxData),
		fn_CxEle0(3, F16::_CxData),
		fn_Cz(3, F16::_CzData),
		fn_CzEle0(3, F16::_CzData),
		fn_Cm(3, F16::_CmData),
		fn_CmEle0(3, F16::_CmData),
		fn_Cy(2, F16::_CyData),
		fn_Cn(3, F16::_CnData),
		fn_CnEle0(3, F16::_CnData),
		fn_Cl(3, F16::_ClData),
		fn_ClEle0(3, F16::_ClData),
		fn_Cx_lef(2, F16::_Cx_lefData),
		fn_Cz_lef(2, F16::_Cz_lefData),
		fn_Cm_lef(2, F16::_Cm_lefData),
		fn_Cy_lef(2, F16::_Cy_lefData),
		fn_Cn_lef(2, F16::_Cn_lefData),
		fn_Cl_lef(2, F16::_Cl_lefData),
		fn_CXq(1, F16::_CxqData),
		fn_CZq(1, F16::_CzqData),
		fn_CMq(1, F16::_CmqData),
		fn_CYp(1, F16::_CypData),
		fn_CYr(1, F16::_CyrData),
		fn_CNr(1, F16::_CnrData),
		fn_CNp(1, F16::_CnpData),
		fn_CLp(1, F16::_ClpData),
		fn_CLr(1, F16::_ClrData),
		fn_delta_CXq_lef(1, F16::_delta_CXq_lefData),
		fn_delta_CYr_lef(1, F16::_delta_CYr_lefData),
		fn_delta_CYp_lef(1, F16::_delta_CYp_lefData),
		fn_delta_CZq_lef(1, F16::_delta_CZq_lefData),
		fn_delta_CLr_lef(1, F16::_delta_CLr_lefData),
		fn_delta_CLp_lef(1, F16::_delta_CLp_lefData),
		fn_delta_CMq_lef(1, F16::_delta_CMq_lefData),
		fn_delta_CNr_lef(1, F16::_delta_CNr_lefData),
		fn_delta_CNp_lef(1, F16::_delta_CNp_lefData),
		fn_Cy_r30(2, F16::_Cy_r30Data),
		fn_Cn_r30(2, F16::_Cn_r30Data),
		fn_Cl_r30(2, F16::_Cl_r30Data),
		fn_Cy_a20(2, F16::_Cy_a20Data),
		fn_Cy_a20_lef(2, F16::_Cy_a20_lefData),
		fn_Cn_a20(2, F16::_Cn_a20Data),
		fn_Cn_a20_lef(2, F16::_Cn_a20_lefData),
		fn_Cl_a20(2, F16::_Cl_a20Data),
		fn_Cl_a20_lef(2, F16::_Cl_a20_lefData),
		fn_delta_CNbeta(1, F16::_delta_CNbetaData),
		fn_delta_CLbeta(1, F16::_delta_CLbetaData),
		fn_delta_Cm(1, F16::_delta_CmData),
		fn_eta_el(1, F16::_eta_elData),
		cgLiftDiff(0.05, 0.30, 0, 2, 0.30, 0.39),
		m_CyAileronLeft(0), m_CnAileronLeft(0), m_ClAileronLeft(0),
		m_CyAileronRight(0), m_CnAileronRight(0), m_ClAileronRight(0),
		m_CyRudder(0), m_CnRudder(0), m_ClRudder(0),
		m_CxFlapLeft(0), m_CxFlapRight(0), m_CzFlapLeft(0), m_CzFlapRight(0),
		m_CxAirbrake(0),
		m_diffCgPCT(0)
	{
		initfn();
	}
	~F16Aero() {}
	void initfn();

	void updateFrame(const F16BodyState &bstate, F16FlightSurface &fsurf, const double frameTime)
	{
		const double alpha = limit(bstate.alpha_DEG, -20.0, 90.0);
		const double beta = limit(bstate.beta_DEG, -30.0, 30.0);

		// TODO: use left and right rudder angles
		// for now, symmetric use
		// TODO: support differential mode
		//const double el = -fsurf.pitch_Command;
		const double el = fsurf.elevon_Left_Command; // just symmetric for now

		// TODO: speed brake handling..
		// TODO Speedbrakes aero (from JBSim F16.xml config)

		/* hifi_C */
		res.fn_Cx = fn_Cx.interpnf3(alpha, beta, el); //CX0120_ALPHA1_BETA1_DH1_201.dat
		res.fn_Cz = fn_Cz.interpnf3(alpha, beta, el); //CZ0120_ALPHA1_BETA1_DH1_301.dat
		res.fn_Cm = fn_Cm.interpnf3(alpha, beta, el); //CM0120_ALPHA1_BETA1_DH1_101.dat
		res.fn_Cy = fn_Cy.interpnf2(alpha, beta); // CY0320_ALPHA1_BETA1_401.dat
		res.fn_Cn = fn_Cn.interpnf3(alpha, beta, el); //CN0120_ALPHA1_BETA1_DH2_501.dat
		res.fn_Cl = fn_Cl.interpnf3(alpha, beta, el);

		// also with zero elevator
		res.fn_CxEle0 = fn_CxEle0.interpnf3(alpha, beta, 0); //CX0120_ALPHA1_BETA1_DH1_201.dat
		res.fn_CzEle0 = fn_CzEle0.interpnf3(alpha, beta, 0); //CZ0120_ALPHA1_BETA1_DH1_301.dat
		res.fn_CmEle0 = fn_CmEle0.interpnf3(alpha, beta, 0); //CM0120_ALPHA1_BETA1_DH1_101.dat
		res.fn_CnEle0 = fn_CnEle0.interpnf3(alpha, beta, 0); //CN0120_ALPHA1_BETA1_DH2_501.dat
		res.fn_ClEle0 = fn_ClEle0.interpnf3(alpha, beta, 0);

		/* hifi_damping */
		res.fn_CXq = fn_CXq.interpnf1(alpha); //CX1120_ALPHA1_204.dat
		res.fn_CYr = fn_CYr.interpnf1(alpha); //CY1320_ALPHA1_406.dat
		res.fn_CYp = fn_CYp.interpnf1(alpha); //CY1220_ALPHA1_408.dat
		res.fn_CZq = fn_CZq.interpnf1(alpha); //CZ1120_ALPHA1_304.dat
		res.fn_CLr = fn_CLr.interpnf1(alpha); //CL1320_ALPHA1_606.dat
		res.fn_CLp = fn_CLp.interpnf1(alpha); //CL1220_ALPHA1_608.dat
		res.fn_CMq = fn_CMq.interpnf1(alpha); //CM1120_ALPHA1_104.dat
		res.fn_CNr = fn_CNr.interpnf1(alpha); //CN1320_ALPHA1_506.dat
		res.fn_CNp = fn_CNp.interpnf1(alpha); //CN1220_ALPHA1_508.dat

		/* hifi_C_lef */ // (leading-edge flap)
		res.fn_Cx_lef = fn_Cx_lef.interpnf2Lim(alpha, beta); //CX0820_ALPHA2_BETA1_202.dat
		res.fn_Cz_lef = fn_Cz_lef.interpnf2Lim(alpha, beta); //CZ0820_ALPHA2_BETA1_302.dat
		res.fn_Cm_lef = fn_Cm_lef.interpnf2Lim(alpha, beta); //CM0820_ALPHA2_BETA1_102.dat
		res.fn_Cy_lef = fn_Cy_lef.interpnf2Lim(alpha, beta); //CY0820_ALPHA2_BETA1_402.dat
		res.fn_Cn_lef = fn_Cn_lef.interpnf2Lim(alpha, beta); //CN0820_ALPHA2_BETA1_502.dat
		res.fn_Cl_lef = fn_Cl_lef.interpnf2Lim(alpha, beta);

		/* hifi_damping_lef */
		res.fn_delta_CXq_lef = fn_delta_CXq_lef.interpnf1Lim(alpha); //CX1420_ALPHA2_205.dat
		res.fn_delta_CYr_lef = fn_delta_CYr_lef.interpnf1Lim(alpha); //CY1620_ALPHA2_407.dat
		res.fn_delta_CYp_lef = fn_delta_CYp_lef.interpnf1Lim(alpha); //CY1520_ALPHA2_409.dat
		res.fn_delta_CZq_lef = fn_delta_CZq_lef.interpnf1Lim(alpha); //CZ1420_ALPHA2_305.dat
		res.fn_delta_CLr_lef = fn_delta_CLr_lef.interpnf1Lim(alpha); //CL1620_ALPHA2_607.dat
		res.fn_delta_CLp_lef = fn_delta_CLp_lef.interpnf1Lim(alpha); //CL1520_ALPHA2_609.dat
		res.fn_delta_CMq_lef = fn_delta_CMq_lef.interpnf1Lim(alpha); //CM1420_ALPHA2_105.dat
		res.fn_delta_CNr_lef = fn_delta_CNr_lef.interpnf1Lim(alpha); //CN1620_ALPHA2_507.dat
		res.fn_delta_CNp_lef = fn_delta_CNp_lef.interpnf1Lim(alpha); //CN1520_ALPHA2_509.dat

		/* hifi_rudder */
		res.fn_Cy_r30 = fn_Cy_r30.interpnf2(alpha, beta); //CY0720_ALPHA1_BETA1_405.dat
		res.fn_Cn_r30 = fn_Cn_r30.interpnf2(alpha, beta); //CN0720_ALPHA1_BETA1_503.dat
		res.fn_Cl_r30 = fn_Cl_r30.interpnf2(alpha, beta); //CL0720_ALPHA1_BETA1_603.dat

		/* hifi_ailerons */
		res.fn_Cy_a20 = fn_Cy_a20.interpnf2(alpha, beta); //CY0620_ALPHA1_BETA1_403.dat
		res.fn_Cn_a20 = fn_Cn_a20.interpnf2(alpha, beta); //CN0620_ALPHA1_BETA1_504.dat
		res.fn_Cl_a20 = fn_Cl_a20.interpnf2(alpha, beta); //CL0620_ALPHA1_BETA1_604.dat

		res.fn_Cy_a20_lef = fn_Cy_a20_lef.interpnf2Lim(alpha, beta); //CY0920_ALPHA2_BETA1_404.dat
		res.fn_Cn_a20_lef = fn_Cn_a20_lef.interpnf2Lim(alpha, beta); //CN0920_ALPHA2_BETA1_505.dat
		res.fn_Cl_a20_lef = fn_Cl_a20_lef.interpnf2Lim(alpha, beta); //CL0920_ALPHA2_BETA1_605.dat

		/* hifi_other_coeffs */
		res.fn_delta_CNbeta = fn_delta_CNbeta.interpnf1(alpha); //CN9999_ALPHA1_brett.dat
		res.fn_delta_CLbeta = fn_delta_CLbeta.interpnf1(alpha); //CL9999_ALPHA1_brett.dat
		res.fn_delta_Cm = fn_delta_Cm.interpnf1(alpha); //CM9999_ALPHA1_brett.dat
		res.fn_eta_el = fn_eta_el.interpnf1(el); //ETA_DH1_brett.dat

		//Cm_delta_ds = 0;       /* ignore deep-stall regime, delta_Cm_ds = 0 */

	}

	// TODO:
	// calculate amount of wing flex (if any)
	// and effect on aerodynamics by it
	void computeWingFlex()
	{
	}

	// calculate side-wind effect on direction, moments etc.
	void sidewind()
	{
	}

	// In low speeds, lift is in front of reference CG,
	// in mach 1 lift is at CG position,
	// over mach 1 lift aft of CG position (towards tail)
	// -> aerodynamic CG is different from "weight" (mass CG)
	// -> this needs to be calculated as function of velocity
	//
	void getAeroCgDiff(const double dynamicPressure_NM2, const double machNumber)
	{
		// CG may vary from 0.30 - 0.39, 0.35 at mach 1 (reference point)
		//const double diffCgPCT = (F16::referenceCG_PCT - F16::actualCG_PCT);

		// as a function of mach number (might be better as Qc/Ps..)
		m_diffCgPCT = cgLiftDiff.result(machNumber);
	}

	/*
	// just putting as note in case there's need to remember..
	//
	double getShearStress()
	{
		tau == F/A; // force per area

		// mu is dynamic viscosity coefficient
		// V is velocity
		// y is height
		tau == mu * (dV / dy); 
	}
	*/

	// just putting equation somewhere I can remember it..
	//
	// Re = (VL) / v
	// ..where:
	// V is velocity of flow
	// L is length of body for flow travel over
	// v is kinematic viscosity of fluid
	//
	double getReynoldsNumber(const double flowVelocity, const double length, const double viscosity) const
	{
		if (viscosity != 0)
		{
			return (flowVelocity * length) / viscosity;
		}
		return 0;
	}
	double getLaminarFlowFriction(const double Re) 
	{
		double Cf = 1.328 / sqrt(Re);

		// note: replace L in Re equation with distance from leading edge, then use below:
		// 
		//Cf = 0.664 / sqrt(Re);
		return Cf;
	}
	double getTurbulentFlowFriction(const double Re)
	{
		double lgre = log(Re);
		double denom = pow(lgre, 2.58);
		double Cf = 0.455 / denom;
		return Cf;
	}

	// flow detachment from boundary layer and change in drag as caused by it
	void computeFlowDetach()
	{
	}

	// at supersonic speeds, compute visous compressible flow
	// (at subsonic, incompressible should suffice)
	// -> also needs some calculation at transonic speeds
	void compressibleFlow()
	{
	}

	// drag caused by aircraft skin in contact with air (friction)
	// see: http://adg.stanford.edu/aa241/drag/wettedarea.html
	//
	// - AFWAL-TM-84-203
	//
	// http://www.cfd-online.com/Wiki/Skin_friction_coefficient
	//
	double getWettedAreaDrag(const double dynamicPressure_NM2, const double machNumber)
	{
		//Swetted = 2.0 * (1 + 0.2 t/c) * Sexposed;

		//SwettedNose = .75 * pi * D * Lnose;
		//SwettedTail = .72 * pi * D * Ltail;
		// ..where:
		// D = diameter of constant section
		// L = length of nose or tail cone

		// Deff = (W/2+H/2)*(64-3*pow(R,4)/(64-16*pow(R,2))
		// ..where:
		// R = (H-W)/(H+W)

		//wing_wetted_area_FT2
		//ventral_fin_each_wetted_area_FT2
		//horiz_tail_wetted_area_FT2
		//vertical_tail_wetted_area_FT2
		//fuselage_wetted_area_FT2

		// TODO: get lookup data for Cf (skin friction coefficient)

		// flat plate, zero pressure gradient..
		// Cf = 1.32824/Re ^1/2
		//
		// Rn = 3 * 10^6, Rn = 40 * 10^6
		// couple of computational methods based on reynolds number:
		// 
		// Cf = 0.455 / ((log Re) * 2.58) - A / Re
		//
		// Cf ^-1/2 = 4.13 * log (Re Cf)

		// if we have Cf, we could calculate Df:
		//
		// Df = (.5*p*V^2) * Cf * Swet
		// -> first part is dynamic pressure, all we need is Cf now..

		// we need viscosity as part of calculation for Reynolds number..
		double visc = pAtmos->getKinematicViscosity();

		// reynolds number over mean chord length
		double reMeanChord = getReynoldsNumber(pAtmos->totalVelocity, F16::meanChord_m, visc);

		// TODO: how can we detect type of flow (laminar or turbulent)
		// at given position in given conditions?
		double CfMeanChord = getLaminarFlowFriction(reMeanChord);

		// skin friction over rest of the body..
		// iterate over length of whole wing surface?

		return 0;
	}

	void getAirbrakeDrag(const double dynamicPressure_NM2, F16FlightSurface &fsurf)
	{
		double airbrakeDrag = 0;

		// TEST!
		// just use full now for testing
		//double force = dynamicPressure_LBFT2 * 16.0 * cos(60) * 0.7;

		/* source: http://www.f-16.net/forum/viewtopic.php?t=11398
		Because landing is such a low speed, I did not bother to calculate those forces.
		But to estimate the force on the speedbrake at landing, you can use the dynamic pressure at landing speed x speedbrake area x cos 60 deg x Cd

		dynamic pressure q ~ 125 lb/sq ft (from q/M^2 = 1480 lb/sq ft)
		area ~ 4 sq ft x 4
		cos 60 deg = .866
		Cd ~ .7

		total drag force ~ 1212 lb

		That is the total force (parallel to the fuselage centerline) on all four panels at landing speed. It is much less than 3 tons.
		*/
		// ~1.48645m^2 area

		//double force = dynamicPressure_LBFT2 * 16.0 * cos(60) * 0.7;
		//double force = dynamicPressure_NM2 * F16::airbrakeArea_m2 * cos(60) * 0.7;

		// symmetric operation, should not make difference which one is used..?
		if (fsurf.airbrake_Left_PCT > 0 || fsurf.airbrake_Right_PCT > 0)
		{
			// for both sides separately?
			//double force = dynamicPressure_NM2 * (F16::airbrakeArea_m2 / 2);
			double force = dynamicPressure_NM2 * F16::airbrakeArea_m2;
			double CDAirbrake = cos(fsurf.airbrake_Left_PCT) * 0.7;

			// TODO: move airbrake integration to motions instead to get it correctly?
			//CDAirbrake *= force;
			airbrakeDrag = -(CDAirbrake);
		}
		else
		{
			airbrakeDrag = 0;
		}
		m_CxAirbrake = airbrakeDrag;
	}

	void getFlapCoeff(const double flap_PCT, const double body_alpha_DEG, double &CzFlap, double &CxFlap) const
	{
		// this does not work correctly when flap and aileron are combined

		// FLAPS (From JBSim F16.xml config)
		double CLFlaps = 0.35 * flap_PCT;
		double CDFlaps = 0.08 * flap_PCT;
		CzFlap = -(CLFlaps * cos(body_alpha_DEG * F16::degtorad) + CDFlaps * sin(F16::degtorad));
		CxFlap = -(-CLFlaps * sin(body_alpha_DEG * F16::degtorad) + CDFlaps * cos(F16::degtorad));
	}
	void getFlapsCoeff(const double dynamicPressure_NM2, const F16FlightSurface &fsurf, const F16BodyState &bstate)
	{
		// TODO: integration of both sides seems to have problem in final stage, check it out

		getFlapCoeff(fsurf.flap_Left_PCT, bstate.alpha_DEG, m_CzFlapLeft, m_CxFlapLeft);
		getFlapCoeff(fsurf.flap_Right_PCT, bstate.alpha_DEG, m_CzFlapRight, m_CxFlapRight);
	}

	double getAileronCoeff(const double fn_C_a20, const double fn_C_a20_lef, const double fn_C, const double fn_C_lef, const double leadingEdgeFlap_PCT, const double flaperon_PCT) const
	{
		//const double leadingEdgeFlap_PCT = fsurf.leadingEdgeFlap_Right_PCT;
		const double C_delta_a20 = fn_C_a20 - fn_C;
		const double C_delta_a20_lef = fn_C_a20_lef - fn_C_lef - C_delta_a20;
		const double dail = C_delta_a20 + C_delta_a20_lef*leadingEdgeFlap_PCT; // <- lef symmetric

		// this does not work correctly when flap and aileron are combined

		// check
		// dail * (fsurf.aileron_Right_PCT + fsurf.aileron_Left_PCT);
		//return dail*fsurf.flaperon_Right_PCT + dail*fsurf.flaperon_Left_PCT;
		return dail*flaperon_PCT;
	}

	void getAileronsCoeff(const F16FlightSurface &fsurf)
	{
		// TODO: integration of both sides seems to have problem in final stage, check it out

		// since lef is symmetric, it does not matter which one is given below
		m_CyAileronLeft = getAileronCoeff(
							res.fn_Cy_a20, res.fn_Cy_a20_lef, res.fn_Cy, res.fn_Cy_lef,
							fsurf.leadingEdgeFlap_Left_PCT, fsurf.flaperon_Left_PCT);
		m_CnAileronLeft = getAileronCoeff(
							res.fn_Cn_a20, res.fn_Cn_a20_lef, res.fn_CnEle0, res.fn_Cn_lef,
							fsurf.leadingEdgeFlap_Left_PCT, fsurf.flaperon_Left_PCT);
		m_ClAileronLeft = getAileronCoeff(
							res.fn_Cl_a20, res.fn_Cl_a20_lef, res.fn_ClEle0, res.fn_Cl_lef, 
							fsurf.leadingEdgeFlap_Left_PCT, fsurf.flaperon_Left_PCT);
		m_CyAileronRight = getAileronCoeff(
							res.fn_Cy_a20, res.fn_Cy_a20_lef, res.fn_Cy, res.fn_Cy_lef,
							fsurf.leadingEdgeFlap_Right_PCT, fsurf.flaperon_Right_PCT);
		m_CnAileronRight = getAileronCoeff(
							res.fn_Cn_a20, res.fn_Cn_a20_lef, res.fn_CnEle0, res.fn_Cn_lef,
							fsurf.leadingEdgeFlap_Right_PCT, fsurf.flaperon_Right_PCT);
		m_ClAileronRight = getAileronCoeff(
							res.fn_Cl_a20, res.fn_Cl_a20_lef, res.fn_ClEle0, res.fn_Cl_lef,
							fsurf.leadingEdgeFlap_Right_PCT, fsurf.flaperon_Right_PCT);
	}

	void getRudderCoeff(const F16FlightSurface &fsurf)
	{
		const double Cy_delta_r30 = res.fn_Cy_r30 - res.fn_Cy;
		const double Cn_delta_r30 = res.fn_Cn_r30 - res.fn_CnEle0;
		const double Cl_delta_r30 = res.fn_Cl_r30 - res.fn_ClEle0;

		m_CyRudder = Cy_delta_r30*fsurf.rudder_PCT;
		m_CnRudder = Cn_delta_r30*fsurf.rudder_PCT;
		m_ClRudder = Cl_delta_r30*fsurf.rudder_PCT;
	}

	/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	compute Cx_tot, Cz_tot, Cm_tot, Cy_tot, Cn_tot, and Cl_total
	(as on NASA report p37-40)
	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
	void computeTotals(F16FlightSurface &fsurf, F16BodyState &bstate,
					const double LgCxGearAero, const double LgCzGearAero)
	{
		// TODO: finish this, integrate to calculations
		double CxWet = getWettedAreaDrag(pAtmos->dynamicPressure, pAtmos->machNumber);

		// in original nlplant there is 2*vt, but is that because lift and drag 
		// are not calculated for both sides separately? (no support for differential deflections)
		const double totalVt = pAtmos->totalVelocity * 2; // 2*vt in original
		double meanChordVt = 0.0;
		double wingSpanVt = 0.0;
		if (totalVt != 0.0)
		{
			meanChordVt = (F16::meanChord_m / totalVt);
			wingSpanVt = (F16::wingSpan_m / totalVt);
		}
		const double meanChordPerWingSpan = (F16::meanChord_m / F16::wingSpan_m);


		// TODO: dynamic CG to calculations, uses hardcoded "real" position now
		// (check: does this actually consider the RSS lift at non-CG position?)
		//
		// In low speeds, lift is in front of reference CG,
		// in mach 1 lift is at CG position,
		// over mach 1 lift aft of CG position (towards tail)
		// -> aerodynamic CG is different from "weight" (mass CG)
		// -> this needs to be calculated as function of velocity
		//
		//const double diffCgPCT = (F16::referenceCG_PCT - F16::actualCG_PCT);

		// get aerodynamic lift position as function of speed (difference from reference CG)
		getAeroCgDiff(pAtmos->totalVelocity, pAtmos->machNumber);
		getFlapsCoeff(pAtmos->dynamicPressure, fsurf, bstate);
		getAirbrakeDrag(pAtmos->dynamicPressure, fsurf);
		getAileronsCoeff(fsurf);
		getRudderCoeff(fsurf);

		/* XXXXXXXX Cx_tot XXXXXXXX */
		sumCxTotal(meanChordVt, LgCxGearAero, fsurf, bstate);

		/* ZZZZZZZZ Cz_tot ZZZZZZZZ */ 
		sumCzTotal(meanChordVt, LgCzGearAero, fsurf, bstate);

		/* MMMMMMMM Cm_tot MMMMMMMM */ 
		sumCmTotal(meanChordVt, fsurf, bstate);

		/* YYYYYYYY Cy_tot YYYYYYYY */
		sumCyTotal(wingSpanVt, fsurf, bstate);

		/* NNNNNNNN Cn_tot NNNNNNNN */ 
		sumCnTotal(wingSpanVt, meanChordPerWingSpan, fsurf, bstate);

		/* LLLLLLLL Cl_total LLLLLLLL */
		sumClTotal(wingSpanVt, fsurf, bstate);
	}

	void sumCxTotal(const double meanChordVt, const double LgCxGearAero, F16FlightSurface &fsurf, F16BodyState &bstate)
	{
		const double leadingEdgeFlap_PCT = fsurf.leadingEdgeFlap_Right_PCT;
		const double Cx_delta_lef = res.fn_Cx_lef - res.fn_CxEle0;

		/* XXXXXXXX Cx_tot XXXXXXXX */
		double dXdQ = meanChordVt * (res.fn_CXq + res.fn_delta_CXq_lef*leadingEdgeFlap_PCT);
		m_Cx_total = res.fn_Cx + Cx_delta_lef*leadingEdgeFlap_PCT + dXdQ*bstate.pitchRate_RPS;

		// TODO: this has problem when both sides are integrated into total, check it out
		m_Cx_total += ((m_CxFlapLeft + m_CxFlapRight) / 2);
		m_Cx_total += LgCxGearAero;

		/* airbrake - testing now*/
		// TODO: move integration to motions instead?
		m_Cx_total += m_CxAirbrake;
	}

	void sumCzTotal(const double meanChordVt, const double LgCzGearAero, F16FlightSurface &fsurf, F16BodyState &bstate)
	{
		const double leadingEdgeFlap_PCT = fsurf.leadingEdgeFlap_Right_PCT;
		const double Cz_delta_lef = res.fn_Cz_lef - res.fn_CzEle0;

		/* ZZZZZZZZ Cz_tot ZZZZZZZZ */
		double dZdQ = meanChordVt * (res.fn_CZq + Cz_delta_lef*leadingEdgeFlap_PCT);
		m_Cz_total = res.fn_Cz + Cz_delta_lef*leadingEdgeFlap_PCT + dZdQ*bstate.pitchRate_RPS;

		// TODO: this has problem when both sides are integrated into total, check it out
		m_Cz_total += ((m_CzFlapLeft + m_CzFlapRight) / 2);
		m_Cz_total += LgCzGearAero;
	}

	void sumCmTotal(const double meanChordVt, F16FlightSurface &fsurf, F16BodyState &bstate)
	{
		const double leadingEdgeFlap_PCT = fsurf.leadingEdgeFlap_Right_PCT;
		const double Cm_delta_lef = res.fn_Cm_lef - res.fn_CmEle0;

		/* MMMMMMMM Cm_tot MMMMMMMM */
		/* ignore deep-stall regime, delta_Cm_ds = 0 */
		double dMdQ = meanChordVt * (res.fn_CMq + res.fn_delta_CMq_lef*leadingEdgeFlap_PCT);

		// moment should be considered as well when flaperons are in differential mode?
		m_Cm_total = res.fn_Cm*res.fn_eta_el + m_Cz_total*m_diffCgPCT;
		m_Cm_total += Cm_delta_lef*leadingEdgeFlap_PCT + dMdQ*bstate.pitchRate_RPS;
		m_Cm_total += res.fn_delta_Cm + 0; // Cm_delta + Cm_delta_ds (0);
	}

	void sumCyTotal(const double wingSpanVt, F16FlightSurface &fsurf, F16BodyState &bstate)
	{
		const double leadingEdgeFlap_PCT = fsurf.leadingEdgeFlap_Right_PCT;
		const double Cy_delta_lef = res.fn_Cy_lef - res.fn_Cy;

		/* YYYYYYYY Cy_tot YYYYYYYY */
		double dYdR = wingSpanVt * (res.fn_CYr + res.fn_delta_CYr_lef*leadingEdgeFlap_PCT);
		double dYdP = wingSpanVt * (res.fn_CYp + res.fn_delta_CYp_lef*leadingEdgeFlap_PCT);
		m_Cy_total = res.fn_Cy + Cy_delta_lef*leadingEdgeFlap_PCT; 

		// TODO: this has problem when both sides are integrated into total, check it out
		m_Cy_total += (m_CyAileronLeft + m_CyAileronRight) / 2;
		m_Cy_total += m_CyRudder + dYdR*bstate.yawRate_RPS + dYdP*bstate.rollRate_RPS;
	}
	void sumCnTotal(const double wingSpanVt, const double meanChordPerWingSpan, F16FlightSurface &fsurf, F16BodyState &bstate)
	{
		const double leadingEdgeFlap_PCT = fsurf.leadingEdgeFlap_Right_PCT;
		const double Cn_delta_lef = res.fn_Cn_lef - res.fn_CnEle0;

		/* NNNNNNNN Cn_tot NNNNNNNN */
		double dNdR = wingSpanVt * (res.fn_CNr + res.fn_delta_CNr_lef*leadingEdgeFlap_PCT);
		double dNdP = wingSpanVt * (res.fn_CNp + res.fn_delta_CNp_lef*leadingEdgeFlap_PCT);
		m_Cn_total = res.fn_Cn + Cn_delta_lef*leadingEdgeFlap_PCT - m_Cy_total*m_diffCgPCT*meanChordPerWingSpan;

		// TODO: this has problem when both sides are integrated into total, check it out
		m_Cn_total += (m_CnAileronLeft + m_CnAileronRight) / 2;
		m_Cn_total += m_CnRudder + dNdR*bstate.yawRate_RPS + dNdP*bstate.rollRate_RPS;
		m_Cn_total += res.fn_delta_CNbeta*bstate.beta_DEG;
	}
	void sumClTotal(const double wingSpanVt, F16FlightSurface &fsurf, F16BodyState &bstate)
	{
		const double leadingEdgeFlap_PCT = fsurf.leadingEdgeFlap_Right_PCT;
		const double Cl_delta_lef = res.fn_Cl_lef - res.fn_ClEle0;

		/* LLLLLLLL Cl_total LLLLLLLL */
		double dLdR = wingSpanVt * (res.fn_CLr + res.fn_delta_CLr_lef*leadingEdgeFlap_PCT);
		double dLdP = wingSpanVt * (res.fn_CLp + res.fn_delta_CLp_lef*leadingEdgeFlap_PCT);
		m_Cl_total = res.fn_Cl + Cl_delta_lef*leadingEdgeFlap_PCT;

		// TODO: this has problem when both sides are integrated into total, check it out
		m_Cl_total += (m_ClAileronLeft + m_ClAileronRight) / 2;
		m_Cl_total += m_ClRudder + dLdR*bstate.yawRate_RPS + dLdP*bstate.rollRate_RPS;
		m_Cl_total += res.fn_delta_CLbeta*bstate.beta_DEG;
	}


	double getCxTotal() const { return m_Cx_total; }
	double getCzTotal() const { return m_Cz_total; }
	double getCmTotal() const { return m_Cm_total; }
	double getCyTotal() const { return m_Cy_total; }
	double getCnTotal() const { return m_Cn_total; }
	double getClTotal() const { return m_Cl_total; }

}; // class F16Aero

void F16Aero::initfn()
{
	fn_Cx.init();
	fn_Cx.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_Cx.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cx.ndinfo.nPoints[2] = F16::dh1_size;
	fn_Cx.m_Xmat[0] = F16::alpha1;
	fn_Cx.m_Xmat[1] = F16::beta1;
	fn_Cx.m_Xmat[2] = F16::dh1;

	fn_CxEle0.init();
	fn_CxEle0.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_CxEle0.ndinfo.nPoints[1] = F16::beta1_size;
	fn_CxEle0.ndinfo.nPoints[2] = F16::dh1_size;
	fn_CxEle0.m_Xmat[0] = F16::alpha1;
	fn_CxEle0.m_Xmat[1] = F16::beta1;
	fn_CxEle0.m_Xmat[2] = F16::dh1;

	fn_Cz.init(); /* alpha,beta,dele */
	fn_Cz.ndinfo.nPoints[0] = F16::alpha1_size;	/* Alpha npoints */
	fn_Cz.ndinfo.nPoints[1] = F16::beta1_size; /* Beta npoints  */
	fn_Cz.ndinfo.nPoints[2] = F16::dh1_size;  /* dele npoints  */
	fn_Cz.m_Xmat[0] = F16::alpha1;
	fn_Cz.m_Xmat[1] = F16::beta1;
	fn_Cz.m_Xmat[2] = F16::dh1;

	fn_CzEle0.init(); /* alpha,beta,dele */
	fn_CzEle0.ndinfo.nPoints[0] = F16::alpha1_size;	/* Alpha npoints */
	fn_CzEle0.ndinfo.nPoints[1] = F16::beta1_size; /* Beta npoints  */
	fn_CzEle0.ndinfo.nPoints[2] = F16::dh1_size;  /* dele npoints  */
	fn_CzEle0.m_Xmat[0] = F16::alpha1;
	fn_CzEle0.m_Xmat[1] = F16::beta1;
	fn_CzEle0.m_Xmat[2] = F16::dh1;

	fn_Cm.init();
	fn_Cm.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_Cm.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cm.ndinfo.nPoints[2] = F16::dh1_size;
	fn_Cm.m_Xmat[0] = F16::alpha1;
	fn_Cm.m_Xmat[1] = F16::beta1;
	fn_Cm.m_Xmat[2] = F16::dh1;

	fn_CmEle0.init();
	fn_CmEle0.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_CmEle0.ndinfo.nPoints[1] = F16::beta1_size;
	fn_CmEle0.ndinfo.nPoints[2] = F16::dh1_size;
	fn_CmEle0.m_Xmat[0] = F16::alpha1;
	fn_CmEle0.m_Xmat[1] = F16::beta1;
	fn_CmEle0.m_Xmat[2] = F16::dh1;

	fn_Cy.init();
	fn_Cy.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_Cy.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cy.m_Xmat[0] = F16::alpha1;
	fn_Cy.m_Xmat[1] = F16::beta1;

	fn_Cn.init();
	fn_Cn.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_Cn.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cn.ndinfo.nPoints[2] = F16::dh2_size;
	fn_Cn.m_Xmat[0] = F16::alpha1;
	fn_Cn.m_Xmat[1] = F16::beta1;
	fn_Cn.m_Xmat[2] = F16::dh2;

	fn_CnEle0.init();
	fn_CnEle0.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_CnEle0.ndinfo.nPoints[1] = F16::beta1_size;
	fn_CnEle0.ndinfo.nPoints[2] = F16::dh2_size;
	fn_CnEle0.m_Xmat[0] = F16::alpha1;
	fn_CnEle0.m_Xmat[1] = F16::beta1;
	fn_CnEle0.m_Xmat[2] = F16::dh2;

	fn_Cl.init();
	fn_Cl.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_Cl.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cl.ndinfo.nPoints[2] = F16::dh2_size;
	fn_Cl.m_Xmat[0] = F16::alpha1;
	fn_Cl.m_Xmat[1] = F16::beta1;
	fn_Cl.m_Xmat[2] = F16::dh2;

	fn_ClEle0.init();
	fn_ClEle0.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_ClEle0.ndinfo.nPoints[1] = F16::beta1_size;
	fn_ClEle0.ndinfo.nPoints[2] = F16::dh2_size;
	fn_ClEle0.m_Xmat[0] = F16::alpha1;
	fn_ClEle0.m_Xmat[1] = F16::beta1;
	fn_ClEle0.m_Xmat[2] = F16::dh2;

	fn_Cx_lef.init();
	fn_Cx_lef.m_xPar1Limit = 45.0;
	fn_Cx_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_Cx_lef.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cx_lef.m_Xmat[0] = F16::alpha2;
	fn_Cx_lef.m_Xmat[1] = F16::beta1;

	fn_Cz_lef.init();
	fn_Cz_lef.m_xPar1Limit = 45.0;
	fn_Cz_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_Cz_lef.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cz_lef.m_Xmat[0] = F16::alpha2;
	fn_Cz_lef.m_Xmat[1] = F16::beta1;

	fn_Cm_lef.init();
	fn_Cm_lef.m_xPar1Limit = 45.0;
	fn_Cm_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_Cm_lef.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cm_lef.m_Xmat[0] = F16::alpha2;
	fn_Cm_lef.m_Xmat[1] = F16::beta1;

	fn_Cy_lef.init();
	fn_Cy_lef.m_xPar1Limit = 45.0;
	fn_Cy_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_Cy_lef.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cy_lef.m_Xmat[0] = F16::alpha2;
	fn_Cy_lef.m_Xmat[1] = F16::beta1;

	fn_Cn_lef.init();
	fn_Cn_lef.m_xPar1Limit = 45.0;
	fn_Cn_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_Cn_lef.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cn_lef.m_Xmat[0] = F16::alpha2;
	fn_Cn_lef.m_Xmat[1] = F16::beta1;

	fn_Cl_lef.init(); /* alpha,beta*/
	fn_Cl_lef.m_xPar1Limit = 45.0;
	fn_Cl_lef.ndinfo.nPoints[0] = F16::alpha2_size;	/* Alpha npoints */
	fn_Cl_lef.ndinfo.nPoints[1] = F16::beta1_size; /* Beta npoints  */
	fn_Cl_lef.m_Xmat[0] = F16::alpha2;
	fn_Cl_lef.m_Xmat[1] = F16::beta1;

	fn_CXq.init();
	fn_CXq.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_CXq.m_Xmat[0] = F16::alpha1;

	fn_CZq.init();
	fn_CZq.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_CZq.m_Xmat[0] = F16::alpha1;

	fn_CMq.init();
	fn_CMq.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_CMq.m_Xmat[0] = F16::alpha1;

	fn_CYp.init();
	fn_CYp.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_CYp.m_Xmat[0] = F16::alpha1;

	fn_CYr.init();
	fn_CYr.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_CYr.m_Xmat[0] = F16::alpha1;

	fn_CNr.init();
	fn_CNr.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_CNr.m_Xmat[0] = F16::alpha1;

	fn_CNp.init();
	fn_CNp.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_CNp.m_Xmat[0] = F16::alpha1;

	fn_CLp.init();
	fn_CLp.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_CLp.m_Xmat[0] = F16::alpha1;

	fn_CLr.init();
	fn_CLr.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_CLr.m_Xmat[0] = F16::alpha1;

	fn_delta_CXq_lef.init();
	fn_delta_CXq_lef.m_xPar1Limit = 45.0;
	fn_delta_CXq_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_delta_CXq_lef.m_Xmat[0] = F16::alpha2;

	fn_delta_CYr_lef.init();
	fn_delta_CYr_lef.m_xPar1Limit = 45.0;
	fn_delta_CYr_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_delta_CYr_lef.m_Xmat[0] = F16::alpha2;

	fn_delta_CYp_lef.init();
	fn_delta_CYp_lef.m_xPar1Limit = 45.0;
	fn_delta_CYp_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_delta_CYp_lef.m_Xmat[0] = F16::alpha2;

	fn_delta_CZq_lef.init();
	fn_delta_CZq_lef.m_xPar1Limit = 45.0;
	fn_delta_CZq_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_delta_CZq_lef.m_Xmat[0] = F16::alpha2;

	fn_delta_CLr_lef.init();
	fn_delta_CLr_lef.m_xPar1Limit = 45.0;
	fn_delta_CLr_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_delta_CLr_lef.m_Xmat[0] = F16::alpha2;

	fn_delta_CLp_lef.init();
	fn_delta_CLp_lef.m_xPar1Limit = 45.0;
	fn_delta_CLp_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_delta_CLp_lef.m_Xmat[0] = F16::alpha2;

	fn_delta_CMq_lef.init();
	fn_delta_CMq_lef.m_xPar1Limit = 45.0;
	fn_delta_CMq_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_delta_CMq_lef.m_Xmat[0] = F16::alpha2;

	fn_delta_CNr_lef.init();
	fn_delta_CNr_lef.m_xPar1Limit = 45.0;
	fn_delta_CNr_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_delta_CNr_lef.m_Xmat[0] = F16::alpha2;

	fn_delta_CNp_lef.init();
	fn_delta_CNp_lef.m_xPar1Limit = 45.0;
	fn_delta_CNp_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_delta_CNp_lef.m_Xmat[0] = F16::alpha2;

	fn_Cy_r30.init();
	fn_Cy_r30.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_Cy_r30.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cy_r30.m_Xmat[0] = F16::alpha1;
	fn_Cy_r30.m_Xmat[1] = F16::beta1;

	fn_Cn_r30.init();
	fn_Cn_r30.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_Cn_r30.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cn_r30.m_Xmat[0] = F16::alpha1;
	fn_Cn_r30.m_Xmat[1] = F16::beta1;

	fn_Cl_r30.init();
	fn_Cl_r30.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_Cl_r30.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cl_r30.m_Xmat[0] = F16::alpha1;
	fn_Cl_r30.m_Xmat[1] = F16::beta1;

	fn_Cy_a20.init();
	fn_Cy_a20.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_Cy_a20.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cy_a20.m_Xmat[0] = F16::alpha1;
	fn_Cy_a20.m_Xmat[1] = F16::beta1;

	fn_Cy_a20_lef.init();
	fn_Cy_a20_lef.m_xPar1Limit = 45.0;
	fn_Cy_a20_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_Cy_a20_lef.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cy_a20_lef.m_Xmat[0] = F16::alpha2;
	fn_Cy_a20_lef.m_Xmat[1] = F16::beta1;

	fn_Cn_a20.init();
	fn_Cn_a20.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_Cn_a20.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cn_a20.m_Xmat[0] = F16::alpha1;
	fn_Cn_a20.m_Xmat[1] = F16::beta1;

	fn_Cn_a20_lef.init();
	fn_Cn_a20_lef.m_xPar1Limit = 45.0;
	fn_Cn_a20_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_Cn_a20_lef.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cn_a20_lef.m_Xmat[0] = F16::alpha2;
	fn_Cn_a20_lef.m_Xmat[1] = F16::beta1;

	fn_Cl_a20.init();
	fn_Cl_a20.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_Cl_a20.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cl_a20.m_Xmat[0] = F16::alpha1;
	fn_Cl_a20.m_Xmat[1] = F16::beta1;

	fn_Cl_a20_lef.init();
	fn_Cl_a20_lef.m_xPar1Limit = 45.0;
	fn_Cl_a20_lef.ndinfo.nPoints[0] = F16::alpha2_size;
	fn_Cl_a20_lef.ndinfo.nPoints[1] = F16::beta1_size;
	fn_Cl_a20_lef.m_Xmat[0] = F16::alpha2;
	fn_Cl_a20_lef.m_Xmat[1] = F16::beta1;

	fn_delta_CNbeta.init();
	fn_delta_CNbeta.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_delta_CNbeta.m_Xmat[0] = F16::alpha1;

	fn_delta_CLbeta.init();
	fn_delta_CLbeta.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_delta_CLbeta.m_Xmat[0] = F16::alpha1;

	fn_delta_Cm.init();
	fn_delta_Cm.ndinfo.nPoints[0] = F16::alpha1_size;
	fn_delta_Cm.m_Xmat[0] = F16::alpha1;

	fn_eta_el.init();
	fn_eta_el.ndinfo.nPoints[0] = F16::dh1_size;
	fn_eta_el.m_Xmat[0] = F16::dh1;
} // F16Aero::initfn()

#endif // ifndef _F16AERO_H_
