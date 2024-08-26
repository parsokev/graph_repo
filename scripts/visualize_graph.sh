#!/usr/bin/env bash

dot -Tpng ./dot_graphs/full_graph.gv -o ./graph_images/full_graph.png
if [ $? -ne 0 ]; then 
echo "Error encountered while attempting to build \"full_graph.png\"."
kill -INT 0
fi

dot -Tpng ./dot_graphs/shortest_path.gv -o ./graph_images/shortest_path.png
if [ $? -ne 0 ]; then 
echo "Error encountered while attempting to build \"shortest_path.png\"."
kill -INT 0
fi