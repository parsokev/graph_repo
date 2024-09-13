#!/usr/bin/env bash

dot -Tpng ./dot_graphs/full_graph.gv -o ./graph_images/full_graph.png
if [ $? -ne 0 ]; then 
echo "Error encountered while attempting to build \"full_graph.png\"."
kill -INT 0
fi


dot -Tpng ./dot_graphs/MST_overlay.gv -o ./graph_images/MST_overlay.png
if [ $? -ne 0 ]; then 
echo "Error encountered while attempting to build \"MST_overlay.png\"."
kill -INT 0
fi