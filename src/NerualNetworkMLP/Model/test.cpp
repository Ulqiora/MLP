//    auto calcNeuronReaction = [this, &layer, &_func](Neuron* neuron) {
//        double sum = 0.0;
//        for (int j = 0; j < layer.getNumOfNeurons(); ++j) {
//            sum += ((layer(j))->getValue() * (*neuron)(j));
//        }
//        neuron->getValue() = _func.use(sum);
//    };
//    using namespace std;

//    vector<unique_ptr<thread> > threads;

//    for (Neuron* neuron : _neurons) {
//        threads.push_back(unique_ptr<thread>(new thread(calcNeuronReaction, neuron)));
//    }

//    for(auto const& thread : threads) {
//        thread->join();
//    }