#pragma once

#include "UHH2/core/include/Particle.h"
#include <map>

/**
 *  @short container class to store the results of the top quark reconstruction
 * 
 * The top quarks reconstruction only applied to semileptonic ttbar events. A
 * ReconstructionHypothesis then consists of finding the lepton, and assigning the jets of the event
 * to either the leptonically decaying top or the hadronically decaying top. In addition
 * to accessing these information (i.e., which jets are assigned to which side, etc.), each
 * hypothesis can have a number of associated *discriminators*. A discriminator is identified
 * by name and is a floating point value meant to measure how 'good' the hypothesis is according to some criterion;
 * see ReconstructionHypothesisDiscriminators.h for different criteria and to fill the discriminators.
 */
class ReconstructionHypothesis {
public:
  LorentzVector toplep_v4() const{return m_toplep_v4;}
  LorentzVector tophad_v4() const{return m_tophad_v4;} 
  LorentzVector neutrino_v4() const{return m_neutrino_v4;} 
  Particle lepton() const{return m_lepton;}
  std::vector<Particle> tophad_jets() const{return m_tophad_jets;}
  std::vector<Particle> toplep_jets() const{return m_toplep_jets;}
  LorentzVector top_v4() const{ return m_lepton.charge() > 0 ? m_toplep_v4 : m_tophad_v4;}
  LorentzVector antitop_v4() const{ return m_lepton.charge() < 0 ? m_toplep_v4 : m_tophad_v4;}
  LorentzVector wlep_v4() const{ return m_neutrino_v4+m_lepton.v4();}
  LorentzVector blep_v4() const{return m_blep_v4;}

  /// get the discriminator value for this hypothesis; thows a runtime_error if it does not exist.
  float discriminator(const std::string & l) const {
      auto it = m_discriminators.find(l);
      if(it == m_discriminators.end()){
          throw std::runtime_error("ReconstructionHypothesis::discriminator: discriminator with label '" + l + "' not set");
      }
      return it->second;
  }
  
  /// test if a discriminator value with a certian label has already been added
  bool has_discriminator(const std::string & label) const {
      return m_discriminators.find(label) != m_discriminators.end();
  }
  
  void set_blep_v4(LorentzVector v4){m_blep_v4=v4;}
  void set_toplep_v4(LorentzVector v4){m_toplep_v4=v4;}
  void set_tophad_v4(LorentzVector v4){m_tophad_v4=v4;} 
  void set_neutrino_v4(LorentzVector v4){m_neutrino_v4=v4;}
  void add_toplep_jet(const Particle & j){m_toplep_jets.push_back(j);}
  void add_tophad_jet(const Particle & j){m_tophad_jets.push_back(j);}
  void set_lepton(const Particle & l){m_lepton = l;}
  void set_discriminator(const std::string & label, float discr){
      m_discriminators[label] = discr;
  }
  
private:
  LorentzVector m_blep_v4;
  LorentzVector m_toplep_v4;
  LorentzVector m_tophad_v4;
  LorentzVector m_neutrino_v4;

  std::vector<Particle> m_tophad_jets;
  std::vector<Particle> m_toplep_jets;
  Particle m_lepton;

  std::map<std::string, float> m_discriminators;
};

