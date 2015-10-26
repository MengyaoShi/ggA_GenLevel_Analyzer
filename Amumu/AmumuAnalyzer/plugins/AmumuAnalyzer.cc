// -*- C++ -*-
//
// Package:    Amumu/AmumuAnalyzer
// Class:      AmumuAnalyzer
// 
/**\class AmumuAnalyzer AmumuAnalyzer.cc Amumu/AmumuAnalyzer/plugins/AmumuAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Mengyao Shi
//         Created:  Mon, 19 Oct 2015 10:59:36 GMT
//
//


// system include files
#include <memory>
#include <map>
#include <string>
#include <vector>
#include "TH1D.h"
#include <math.h>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
 #include "DataFormats/Candidate/interface/Candidate.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

//
// class declaration
//
using namespace std;
using namespace edm;
using namespace reco;

class AmumuAnalyzer : public edm::EDAnalyzer {
   public:
      explicit AmumuAnalyzer(const edm::ParameterSet&);
      ~AmumuAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
      
   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      edm::InputTag genParticleTag_;
      double mass;
      std::map<std::string, TH1D*> histos1D_;
      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
//
AmumuAnalyzer::AmumuAnalyzer(const edm::ParameterSet& iConfig):
 genParticleTag_(iConfig.getParameter<edm::InputTag>("genParticleTag")),
 histos1D_()
{
}
AmumuAnalyzer::~AmumuAnalyzer()
{

   // do anything here that needs to be done at desctruction time
   //    // (e.g. close files, deallocate resources etc.)
   //
}

void AmumuAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  std::cout<<"enter analyze"<<std::endl; 
  //now do what ever initialization is needed
  edm::Handle<reco::GenParticleCollection> pGenParticles;
  iEvent.getByLabel(genParticleTag_, pGenParticles);
  for(reco::GenParticleCollection::const_iterator iGenParticle = pGenParticles->begin(); iGenParticle != pGenParticles->end(); ++iGenParticle){
    std::cout<< "an iGenParticle appear" << std::endl;
    if((*iGenParticle).pdgId() == 36 && ((*iGenParticle).numberOfDaughters()==2))
    {
      reco::GenParticleRef child0 = iGenParticle->daughterRef(0);
      reco::GenParticleRef child1 = iGenParticle->daughterRef(1);
      std::cout << "\tmom pdgid=" << iGenParticle->pdgId() << "\tchild0 pdgid=" << child0->pdgId() <<"\tchild1 pdgid=" << child1->pdgId() << std::endl;
      if((child0->pdgId() == 13 && child1->pdgId()==-13 )||(child0->pdgId() == -13 && child1->pdgId()==13 ))
      { 
        mass=0.0;
        mass=sqrt((child1->energy()+child0->energy())*(child1->energy()+child0->energy())
		-(child1->px()+child0->px())*(child1->px()+child0->px())
		-(child1->py()+child0->py())*(child1->py()+child0->py())
		-(child1->pz()+child0->pz())*(child1->pz()+child0->pz()));
        std::cout<< "sqrt 2 is " << sqrt(2.0) << std::endl;
        reco::LeafCandidate::LorentzVector sum;
        //sum=child0->p4() + child1->p4();
        histos1D_[ "test" ]->Fill((*iGenParticle).mass());
        std::cout<< "mass is" << mass <<std::endl;

      }     
    }
  }  
}

//
// member functions
//

// ------------ method called for each event  ------------


// ------------ method called once each job just before starting event loop  ------------
void 
AmumuAnalyzer::beginJob()
{
  edm::Service< TFileService > fileService;
  histos1D_[ "test" ]=fileService->make< TH1D >("test", "invariant mass of a from DiMuon", 120, 0, 1200);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
AmumuAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
/*
void 
AmumuAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a run  ------------
/*
void 
AmumuAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when starting to processes a luminosity block  ------------
/*
void 
AmumuAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method called when ending the processing of a luminosity block  ------------
/*
void 
AmumuAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
AmumuAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(AmumuAnalyzer);
