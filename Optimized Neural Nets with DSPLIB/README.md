# Optimizing Artificial Neural Nets with DSPLIB


## System Overview
![system](https://g.gravizo.com/svg? digraph train{rankdir=LR subgraph train{train_data-> train_cpu [style=dotted, label="load"] train_cpu -> train_cpu [style=bold,label=" Train N times"] train_cpu -> output_model [style=bold,label=" output file"] train_data [shape="box3d", style="filled", fillcolor="hotpink", label="Training Data"] train_cpu [shape="tripleoctagon", label="x86 CPU", style="filled", color="lightgreen"] output_model [shape=folder, style=filled, color="blue", fillcolor=".7 .3 1.0", label=" .MODEL"]}subgraph predict{test_data -> DSP [label="preprocess"] output_model -> DSP [style=dotted, label="load"] DSP [shape="doubleoctagon",style="filled",color="lightgreen"] DSP -> prediction [style="bold", color="hotpink"] test_data [shape="box3d", style="filled", fillcolor="pink", label="Test Data"] prediction [shape=diamond,style="filled", color="hotpink", fillcolor="gold", label="Prediction"]}})
