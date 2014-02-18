//=====================================================================-*-C++-*-
// File and Version Information:
//      $Id: RooUnfoldErrors.h,v 1.1 2013/02/18 14:49:20 marone Exp $
//
// Description:
//      Graph Drawing Class for use with RooUnfold.
//
// Authors: Tim Adye <T.J.Adye@rl.ac.uk> and Richard Claridge <richard.claridge@stfc.ac.uk>
//
//==============================================================================

#ifndef ROOUNFOLDERRORS_H_
#define ROOUNFOLDERRORS_H_

#include "TNamed.h"

class TH1;
class RooUnfold;
class TNtuple;

class RooUnfoldErrors : public TNamed {

public:
  
  int toys; // Number of toys 
  RooUnfold* unfold; // Input unfolding object
  const TH1* hTrue;
  RooUnfoldErrors (int NToys,RooUnfold* unfold,const TH1* Truth=0);
  virtual ~RooUnfoldErrors();
  TNtuple* Chi2(); 

  TH1* RMSResiduals();
  TH1* UnfoldingError();

private:
  void CreatePlots();
  void CreatePlotsWithChi2();
  TH1* h_err; // Output plot
  TH1* h_err_res; // Output plot
  TNtuple* hchi2;  // Output plot 
  void GraphParameters(); //
  double xlo; // Minimum x-axis value 
  double xhi; // Maximum x-axis value
  int ntx; // Number of bins in true distribution
  
public:

  ClassDef (RooUnfoldErrors, 0)  // Show unfolding errors
};

#endif
