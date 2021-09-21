/*
 * Copyright 2021 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <adf.h>
#include "kernels.h"

using namespace adf;

class blobFromImagegraph : public adf::graph {
   private:
    kernel k1;

   public:
    port<input> in1;
    port<output> out;

    blobFromImagegraph() {
        k1 = kernel::create(blobFromImage);

        // blob processes 4096 32b blocks or 16384 byte blocks
        connect<adf::window<16384> >(in1, k1.in[0]);

        // blob window passsed directly to output
        connect<window<16384> >(k1.out[0], out);

        source(k1) = "xf_blobfromimage.cc";

        // Initial mapping
        runtime<ratio>(k1) = 0.5;
    };
};

#endif