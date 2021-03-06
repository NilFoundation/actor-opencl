//---------------------------------------------------------------------------//
// Copyright (c) 2011-2019 Dominik Charousset
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the terms and conditions of the BSD 3-Clause License or
// (at your option) under the terms and conditions of the Boost Software
// License 1.0. See accompanying files LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt.
//---------------------------------------------------------------------------//

#pragma once

#include <nil/actor/opencl/actor_facade.hpp>

namespace nil {
    namespace actor {
        namespace detail {

            struct tuple_construct {};

            template<bool PassConfig, class... Ts>
            struct cl_spawn_helper {
                using impl = opencl::actor_facade<PassConfig, Ts...>;
                using map_in_fun = typename impl::input_mapping;
                using map_out_fun = typename impl::output_mapping;

                actor operator()(actor_config actor_cfg, const opencl::program_ptr p, const char *fn,
                                 const opencl::nd_range &range, Ts &&... xs) const {
                    return actor_cast<actor>(impl::create(std::move(actor_cfg), p, fn, range, map_in_fun {},
                                                          map_out_fun {}, std::forward<Ts>(xs)...));
                }

                actor operator()(actor_config actor_cfg, const opencl::program_ptr p, const char *fn,
                                 const opencl::nd_range &range, map_in_fun map_input, Ts &&... xs) const {
                    return actor_cast<actor>(impl::create(std::move(actor_cfg), p, fn, range, std::move(map_input),
                                                          map_out_fun {}, std::forward<Ts>(xs)...));
                }

                actor operator()(actor_config actor_cfg, const opencl::program_ptr p, const char *fn,
                                 const opencl::nd_range &range, map_in_fun map_input, map_out_fun map_output,
                                 Ts &&... xs) const {
                    return actor_cast<actor>(impl::create(std::move(actor_cfg), p, fn, range, std::move(map_input),
                                                          std::move(map_output), std::forward<Ts>(xs)...));
                }
            };
        }    // namespace detail
    }        // namespace actor
}    // namespace nil
