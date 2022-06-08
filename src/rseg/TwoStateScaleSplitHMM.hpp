/*
 * Copyright (C) 2011 University of Southern California
 *                    Andrew D Smith and Qiang Song
 * Author: Qiang Song and Andrew D. Smith
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

#ifndef TWO_STATE_SCALE_SPLIT_HMM_HPP
#define TWO_STATE_SCALE_SPLIT_HMM_HPP

#include "smithlab_utils.hpp"
#include "SplitDistro.hpp"

class TwoStateScaleSplitHMM {
public:

  TwoStateScaleSplitHMM(const double mp, const double tol,
		   const size_t max_itr, const bool v, bool d = false) :
    MIN_PROB(mp), tolerance(tol), max_iterations(max_itr),
    VERBOSE(v), DEBUG(d) {}

  double
  ViterbiDecoding(const std::vector<double> &values,
                const std::vector<double> &scales,
		  const std::vector<size_t> &reset_points,
		  const std::vector<double> &start_trans,
		  const std::vector<std::vector<double> > &trans,
		  const std::vector<double> &end_trans,
		  const SplitDistro &fg_distro,
		  const SplitDistro &bg_distro,
		  std::vector<bool> &ml_classes) const;

  double
  BaumWelchTraining(const std::vector<double> &values,
		    const std::vector<double> &vals_a,
		    const std::vector<double> &vals_b,
            const std::vector<double> &scales,
		    const std::vector<size_t> &reset_points,
		    std::vector<double> &start_trans,
		    std::vector<std::vector<double> > &trans,
		    std::vector<double> &end_trans,
		    SplitDistro &fg_distro,
		    SplitDistro &bg_distro) const;

  double
  PosteriorDecoding(const std::vector<double> &values,
                    const std::vector<double> &scales,
		    const std::vector<size_t> &reset_points,
		    const std::vector<double> &start_trans,
		    const std::vector<std::vector<double> > &trans,
		    const std::vector<double> &end_trans,
		    const SplitDistro &fg_distro,
		    const SplitDistro &bg_distro,
		    std::vector<bool> &classes,
		    std::vector<double> &llr_scores) const;

  void
  PosteriorScores(const std::vector<double> &values,
                  const std::vector<double> &scales,
		  const std::vector<size_t> &reset_points,
		  const std::vector<double> &start_trans,
		  const std::vector<std::vector<double> > &trans,
		  const std::vector<double> &end_trans,
		  const SplitDistro &fg_distro,
		  const SplitDistro &bg_distro,
		  const std::vector<bool> &classes,
		  std::vector<double> &llr_scores) const;

  void
  PosteriorScores(const std::vector<double> &values,
                  const std::vector<double> &scales,
		  const std::vector<size_t> &reset_points,
		  const std::vector<double> &start_trans,
		  const std::vector<std::vector<double> > &trans,
		  const std::vector<double> &end_trans,
		  const SplitDistro &fg_distro,
		  const SplitDistro &bg_distro,
		  const bool class_id,
		  std::vector<double> &llr_scores) const;

  void
  TransitionPosteriors(const std::vector<double> &values,
                       const std::vector<double> &scales,
		       const std::vector<size_t> &reset_points,
		       const std::vector<double> &start_trans,
		       const std::vector<std::vector<double> > &trans,
		       const std::vector<double> &end_trans,
		       const SplitDistro &fg_distro,
		       const SplitDistro &bg_distro,
		       const size_t transition,
		       std::vector<double> &scores) const;

  void
  TransitionPosteriors(
      const std::vector<double> &values,
      const std::vector<double> &scales,
      const std::vector<size_t> &reset_points,
      const std::vector<double> &start_trans,
      const std::vector<std::vector<double> > &trans,
      const std::vector<double> &end_trans,
      const SplitDistro &fg_distro,
      const SplitDistro &bg_distro,
      std::vector<std::vector<std::vector<double> > > &post_trans_scores) const;

  std::string
  error_log() const;

  static const size_t FG_TO_FG_TRANSITION = 0;
  static const size_t FG_TO_BG_TRANSITION = 1;
  static const size_t BG_TO_FG_TRANSITION = 2;
  static const size_t BG_TO_BG_TRANSITION = 3;

private:

  double
  ViterbiDecoding(const std::vector<double> &values,
                  const std::vector<double> &scales,
		  const std::vector<size_t> &reset_points,
		  double p_sf, double p_sb,
		  double p_ff, double p_fb, double p_ft,
		  double p_bf, double p_bb, double p_bt,
		  const SplitDistro &fg_distro,
		  const SplitDistro &bg_distro,
		  std::vector<bool> &ml_classes) const;

  double
  BaumWelchTraining(const std::vector<double> &values,
		    const std::vector<double> &vals_a,
		    const std::vector<double> &vals_b,
            const std::vector<double> &scales,
		    const std::vector<size_t> &reset_points,
		    double &p_sf, double &p_sb,
		    double &p_ff, double &p_fb, double &p_ft,
		    double &p_bf, double &p_bb, double &p_bt,
		    SplitDistro &fg_distro,
		    SplitDistro &bg_distro) const;

  double
  PosteriorDecoding(const std::vector<double> &values,
                    const std::vector<double> &scales,
		    const std::vector<size_t> &reset_points,
		    double p_sf, double p_sb,
		    double p_ff, double p_fb, double p_ft,
		    double p_bf, double p_bb, double p_bt,
		    const SplitDistro &fg_distro,
		    const SplitDistro &bg_distro,
		    std::vector<bool> &classes,
		    std::vector<double> &llr_scores) const;

  void
  PosteriorScores(const std::vector<double> &values,
                  const std::vector<double> &scales,
		  const std::vector<size_t> &reset_points,
		  double p_sf, double p_sb,
		  double p_ff, double p_fb, double p_ft,
		  double p_bf, double p_bb, double p_bt,
		  const SplitDistro &fg_distro,
		  const SplitDistro &bg_distro,
		  const std::vector<bool> &classes,
		  std::vector<double> &llr_scores) const;

  void
  PosteriorScores(const std::vector<double> &values,
                  const std::vector<double> &scales,
		  const std::vector<size_t> &reset_points,
		  double p_sf, double p_sb,
		  double p_ff, double p_fb, double p_ft,
		  double p_bf, double p_bb, double p_bt,
		  const SplitDistro &fg_distro,
		  const SplitDistro &bg_distro,
		  const bool class_id,
		  std::vector<double> &llr_scores) const;

  void
  TransitionPosteriors(const std::vector<double> &values,
                       const std::vector<double> &scales,
		       const std::vector<size_t> &reset_pointsints,
		       double p_sf, double p_sb,
		       double p_ff, double p_fb, double p_ft,
		       double p_bf, double p_bb, double p_bt,
		       const SplitDistro &fg_distro,
		       const SplitDistro &bg_distro,
		       const size_t transition,
		       std::vector<double> &scores) const;
  void
  TransitionPosteriors(
      const std::vector<double> &values,
      const std::vector<double> &scales,
      const std::vector<size_t> &reset_pointsints,
      double p_sf, double p_sb,
      double p_ff, double p_fb, double p_ft,
      double p_bf, double p_bb, double p_bt,
      const SplitDistro &fg_distro,
      const SplitDistro &bg_distro,
      std::vector<std::vector< std::vector<double> > > &post_trans_scores) const;

  double
  single_iteration(const std::vector<double> &values,
                   const std::vector<double> &scales,
		   const std::vector<double> &vals_a,
		   const std::vector<double> &vals_b,
		   const std::vector<size_t> &reset_points,
		   std::vector<std::pair<double, double> > &forward,
		   std::vector<std::pair<double, double> > &backward,
		   double &p_sf, double &p_sb,
		   double &p_ff, double &p_fb, double &p_ft,
		   double &p_bf, double &p_bb, double &p_bt,
		   SplitDistro &fg_distro,
		   SplitDistro &bg_distro) const;

  double
  forward_algorithm(const std::vector<double> &vals,
                    const std::vector<double> &scales,
		    const size_t start, const size_t end,
		    const double lp_sf, const double lp_sb,
		    const double lp_ff, const double lp_fb, const double lp_ft,
		    const double lp_bf, const double lp_bb, const double lp_bt,
		    const SplitDistro &fg_distro,
		    const SplitDistro &bg_distro,
		    std::vector<std::pair<double, double> > &f) const;
  double
  backward_algorithm(const std::vector<double> &vals,
                     const std::vector<double> &scales,
		     const size_t start, const size_t end,
		     const double lp_sf, const double lp_sb,
		     const double lp_ff, const double lp_fb, const double lp_ft,
		     const double lp_bf, const double lp_bb, const double lp_bt,
		     const SplitDistro &fg_distro,
		     const SplitDistro &bg_distro,
		     std::vector<std::pair<double, double> > &b) const;

  double
  log_sum_log_vec(const std::vector<double> &vals, size_t limit) const;

  void
  estimate_emissions(const std::vector<std::pair<double, double> > &f,
		     const std::vector<std::pair<double, double> > &b,
		     std::vector<double> &fg_probs,
		     std::vector<double> &bg_probs) const;

  void
  estimate_transitions(const std::vector<double> &vals,
                       const std::vector<double> &scales,
		       const size_t start, const size_t end,
		       const std::vector<std::pair<double, double> > &f,
		       const std::vector<std::pair<double, double> > &b,
		       const double total,
		       const SplitDistro &fg_distro,
		       const SplitDistro &bg_distro,
		       const double lp_ff, const double lp_fb,
		       const double lp_bf, const double lp_bb,
		       const double lp_ft, const double lp_bt,
		       std::vector<double> &ff_vals,
		       std::vector<double> &fb_vals,
		       std::vector<double> &bf_vals,
		       std::vector<double> &bb_vals) const;

  double
  log_sum_log(const double p, const double q) const;

  double MIN_PROB;
  double tolerance;
  size_t max_iterations;
  bool VERBOSE;
  bool DEBUG;

  mutable size_t emission_correction_count;
};

#endif
