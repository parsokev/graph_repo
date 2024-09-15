#!/usr/bin/env bash

dot -Tpng ./dot_graphs/full_graph.gv -o ./graph_images/full_graph.png
if [ $? -ne 0 ]; then 
echo "Error encountered while attempting to build \"full_graph.png\"."
kill -INT 0
fi


dot -Tpng ./dot_graphs/shortest_path_overlay.gv -o ./graph_images/shortest_path_overlay.png
if [ $? -ne 0 ]; then 
echo "Error encountered while attempting to build \"short_path_overlay.png\"."
kill -INT 0
fi