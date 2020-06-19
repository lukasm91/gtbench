/*
 * gtbench
 *
 * Copyright (c) 2014-2020, ETH Zurich
 * Copyright (c) 2020, NVIDIA
 * All rights reserved.
 *
 * Please, refer to the LICENSE file in the root directory.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#pragma once

#include "./computation.hpp"

namespace numerics {
namespace advection {

class horizontal {
  using p_out = gt::arg<0, storage_t>;
  using p_in = gt::arg<1, storage_t>;
  using p_u = gt::arg<2, storage_t>;
  using p_v = gt::arg<3, storage_t>;
  using p_dx = gt::arg<4, global_parameter_t>;
  using p_dy = gt::arg<5, global_parameter_t>;
  using p_dt = gt::arg<6, global_parameter_t>;

public:
  horizontal(vec<std::size_t, 3> const &resolution,
             vec<real_t, 3> const &delta);

  void operator()(storage_t &out, storage_t const &in, storage_t const &u,
                  storage_t const &v, real_t dt);

private:
  gt::computation<p_out, p_in, p_u, p_v, p_dt> comp_;
};

class vertical {
  storage_ij_t::storage_info_t sinfo_ij_;
  storage_t::storage_info_t sinfo_;

  using p_data_in = gt::arg<0, storage_t>;
  using p_data_out = gt::arg<1, storage_t>;

  using p_dz = gt::arg<2, global_parameter_t>;
  using p_dt = gt::arg<3, global_parameter_t>;

  using p_c = gt::tmp_arg<6, storage_t>;
  using p_d = gt::arg<7, storage_t>;
  using p_d_uncached = gt::arg<14, storage_t>;
  storage_t d_;

  using p_c2 = gt::tmp_arg<21, storage_t>;
  using p_d2 = gt::arg<22, storage_t>;
  using p_d2_uncached = gt::arg<16, storage_t>;
  storage_t d2_;

  using p_alpha = gt::arg<8, storage_ij_t>;
  storage_ij_t alpha_;
  using p_gamma = gt::arg<10, storage_ij_t>;
  storage_ij_t gamma_;
  using p_fact = gt::arg<11, storage_ij_t>;
  storage_ij_t fact_;
  using p_data_in_tmp = gt::arg<12, storage_ij_t>;
  storage_ij_t data_in_tmp_;

  using p_w = gt::arg<17, storage_t>;

  using p_k_size = gt::arg<18, global_parameter_int_t>;
  using p_data_p1_k_cache = gt::tmp_arg<19, storage_t>;
  using p_a_c_cache = gt::tmp_arg<20, storage_t>;

public:
  vertical(vec<std::size_t, 3> const &resolution, vec<real_t, 3> const &delta);

  void operator()(storage_t &out, storage_t const &in, storage_t const &w,
                  real_t dt);

private:
  gt::computation<p_data_in, p_data_out, p_w, p_dt> comp_;
};

class runge_kutta_step {
  storage_ij_t::storage_info_t sinfo_ij_;
  storage_t::storage_info_t sinfo_;

  using p_data_in = gt::arg<0, storage_t>;
  using p_data_in0 = gt::arg<1, storage_t>;
  using p_data_out = gt::arg<2, storage_t>;

  using p_dx = gt::arg<3, global_parameter_t>;
  using p_dy = gt::arg<4, global_parameter_t>;
  using p_dz = gt::arg<5, global_parameter_t>;
  using p_dt = gt::arg<6, global_parameter_t>;

  using p_c = gt::tmp_arg<9, storage_t>;
  using p_d = gt::arg<10, storage_t>;
  using p_d_uncached = gt::arg<17, storage_t>;
  storage_t d_;
  using p_c2 = gt::tmp_arg<26, storage_t>;
  using p_d2 = gt::arg<27, storage_t>;
  using p_d2_uncached = gt::arg<19, storage_t>;
  storage_t d2_;

  using p_alpha = gt::arg<11, storage_ij_t>;
  storage_ij_t alpha_;
  using p_gamma = gt::arg<13, storage_ij_t>;
  storage_ij_t gamma_;
  using p_fact = gt::arg<14, storage_ij_t>;
  storage_ij_t fact_;

  using p_u = gt::arg<20, storage_t>;
  using p_v = gt::arg<21, storage_t>;
  using p_w = gt::arg<22, storage_t>;

  using p_k_size = gt::arg<23, global_parameter_int_t>;

  using p_data_p1_k_cache = gt::tmp_arg<24, storage_t>;
  using p_a_c_cache = gt::tmp_arg<25, storage_t>;

public:
  runge_kutta_step(vec<std::size_t, 3> const &resolution,
                   vec<real_t, 3> const &delta);

  void operator()(storage_t &out, storage_t const &in, storage_t const &in0,
                  storage_t const &u, storage_t const &v, storage_t const &w,
                  real_t dt);

private:
  gt::computation<p_data_in, p_w, p_dt> comp1_;
  gt::computation<p_data_out, p_data_in, p_data_in0, p_u, p_v, p_dt> comp2_;
};

} // namespace advection
} // namespace numerics
