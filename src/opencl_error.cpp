//---------------------------------------------------------------------------//
// Copyright (c) 2011-2019 Dominik Charousset
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the terms and conditions of the BSD 3-Clause License or
// (at your option) under the terms and conditions of the Boost Software
// License 1.0. See accompanying files LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt.
//---------------------------------------------------------------------------//

#include <nil/actor/opencl/opencl_error.hpp>

#include <nil/actor/logger.hpp>

namespace nil {
    namespace actor {
        namespace opencl {

            void throwcl(const char *, cl_int err) {
                if (err != CL_SUCCESS) {
                    ACTOR_RAISE_ERROR("throwcl: unrecoverable OpenCL error");
                }
            }

            void CL_CALLBACK pfn_notify(const char *errinfo, const void *, size_t, void *) {
                ACTOR_LOG_ERROR("\n##### Error message via pfn_notify #####\n"
                                << errinfo << "\n########################################");
                ACTOR_IGNORE_UNUSED(errinfo);
            }
        }    // namespace opencl
    }        // namespace actor
}    // namespace nil
