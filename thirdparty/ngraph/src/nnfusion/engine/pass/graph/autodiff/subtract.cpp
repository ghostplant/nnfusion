//*****************************************************************************
// Copyright 2017-2020 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************


#include "backward_registry.hpp"

REGISTER_BACKWARD_TRANSLATOR(Subtract).translator([](std::shared_ptr<GNode> forward_node,
                                                     const GNodeIndexVector& outputs_grad,
                                                     std::shared_ptr<nnfusion::graph::Graph> graph)
                                                      -> GNodeIndexVector {
    NNFUSION_CHECK(outputs_grad.size() == 1) << "subtract have only 1 output, but "
                                             << outputs_grad.size() << " outputs_grad provided";
    auto neg_out_grad = graph->add_node_and_edge(std::make_shared<op::Negative>(), outputs_grad);
    return GNodeIndexVector{outputs_grad[0], GNodeIndex{neg_out_grad, 0}};
});