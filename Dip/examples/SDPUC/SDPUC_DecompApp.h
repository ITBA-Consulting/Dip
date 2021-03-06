//===========================================================================//
// This file is part of the Decomp Solver Framework.                         //
//                                                                           //
// Decomp is distributed under the Common Public License as part of the      //
// COIN-OR repository (http://www.coin-or.org).                              //
//                                                                           //
// Authors: Matthew Galati, SAS Institute Inc. (matthew.galati@sas.com)      //
//          Ted Ralphs, Lehigh University (ted@lehigh.edu)                   //
//          Jiadong Wang, Lehigh University (jiw408@lehigh.edu)              //
//                                                                           //
// Copyright (C) 2002-2015, Lehigh University, Matthew Galati, and Ted Ralphs//
// All Rights Reserved.                                                      //
//===========================================================================//

#ifndef MCF_DECOMPAPP_INCLUDED
#define MCF_DECOMPAPP_INCLUDED

//===========================================================================//
#include "DecompApp.h"

//===========================================================================//
#include "SDPUC_Instance.h"
#include "SDPUC_Param.h"
//===========================================================================//

//===========================================================================//
/*!
 * \class MCF_DecompApp
 * A DecompApp for solving the 
 *     (Integer) Multi-Commodity Flow Problem (MCF)
 * 
 * \see
 * DecompApp
 *
 */

//===========================================================================//
class SDPUC_DecompApp : public DecompApp {
private:
   /** Class id tag (for log / debugging). */
   const string m_classTag;

   /** Application specific parameters. */
   SDPUC_Param m_appParam;  

   /** SDPUC problem instance data */
   SDPUC_Instance m_instance;

   /** The model objective coefficients (original space). */
   double * m_objective;

   /** Model constraint systems. */
   vector<DecompConstraintSet*> m_models;

public:
   /** @name Helper functions (public). */   

   /** Initialize application. */
   void initializeApp();

   /* Create models. */
   void createModels();
   void createModelCore(DecompConstraintSet * model);
   void createModelRelax(DecompConstraintSet * model,
                         int                   commId);
   void createModelRelaxSparse(DecompConstraintSet * model,
                               int                   commId);
   void createModelMasterOnlys(vector<int> & masterOnlyCols);

   /* Initialise solution */
   DecompSolution createInitialSolution();

      /* Get Instance */
   SDPUC_Instance & getInstance() {return m_instance;}
   /* Get Objective */
   double * getObjective() {return m_objective;}

public:
   /** @name Constructor and Destructor */
   
   /** Default constructor. Takes an instance of UtilParameters */
   SDPUC_DecompApp(UtilParameters & utilParam) :
      DecompApp   (utilParam),
      m_classTag  ("SDPUC-APP"),
      m_objective (NULL)
   {
      //---
      //--- get application parameters
      //---
      m_appParam.getSettings(utilParam);
      if(m_appParam.LogLevel >= 1)
	 m_appParam.dumpSettings();

      initializeApp();                    
   }
   
   virtual ~SDPUC_DecompApp() {
      UTIL_DELARR(m_objective);
      UtilDeleteVectorPtr(m_models);
   };
};

#endif
