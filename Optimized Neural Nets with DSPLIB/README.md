# Optimizing Artificial Neural Nets with DSPLIB


## TODO (*will vanish upon completion*)
* [ ] System Overview
* [ ] Training code for Host CPU
* [ ] DSPLIB optimized Inference code for C6000
* [ ] Additional activation functions [tanh, relu]
* [ ] Dealing with memory/CPU tradeoff w.r.t. act. func/ eval. (look-up tbl vs math ops)
* [ ] Performance Evaluation


## System Overview
![OpType Performance](https://github.com/arjun372/lcdk-guide-for-the-impatient-soul/blob/master/Optimized%20Neural%20Nets%20with%20DSPLIB/charts/overview.png)

<!-- ## System Overview
![Alt text](https://g.gravizo.com/svg?
  digraph train {
    rankdir=LR
    subgraph train
    {
      train_data-> train_cpu [style=dotted, label="load"]
      train_cpu -> train_cpu [style=bold,label=" Train N times"]
      train_cpu -> output_model [style=bold,label= "  output file"]
      train_data [shape="box3d", style="filled", fillcolor="hotpink", label="Training Data"]
      train_cpu [shape="tripleoctagon", label="x86 CPU", style="filled", color = "lightgreen"]
      output_model [shape=folder, style=filled, color="blue", fillcolor=".7 .3 1.0", label=" .MODEL"]
    }
    subgraph predict
    {
      test_data -> DSP [label="preprocess"]
      output_model -> DSP [style=dotted, label="load"]
      DSP [shape="doubleoctagon",style="filled",color="lightgreen"]
      DSP -> prediction [style="bold", color="hotpink"]
      test_data [shape="box3d", style="filled", fillcolor="pink", label="Test Data"]
      prediction [shape=diamond,style="filled", color="hotpink", fillcolor="gold", label="Prediction"]
    }
  }
) -->
