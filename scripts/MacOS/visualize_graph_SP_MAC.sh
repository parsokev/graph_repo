#!/opt/homebrew/bin/bash

# Attempt to generate image of entire processed graph using graphwiz
dot -Tpng:cairo ./dot_graphs/full_graph.gv -o ./graph_images/full_graph.png
if [ $? -ne 0 ]; then
    echo ""
    echo "VISUALIZATION ERROR DETECTED: An error was encountered while attempting to generate the image for the Complete Graph within \"full_graph.png\""
    echo "Please view the lines printed immediately above these to determine the potential nature of the detected errors"
    echo "For further information on feature access and troubleshooting please view the README: https://github.com/parsokev/graph_repo"
    echo ""
else
    echo "Success! The generated image of the COMPLETE GRAPH can now be viewed at \"graph_images/full_graph.png\""
fi

# Attempt to generate image of shortest path overlaying the entire processed graph using graphwiz
dot -Tpng:cairo ./dot_graphs/shortest_path_overlay.gv -o ./graph_images/shortest_path_overlay.png
if [ $? -ne 0 ]; then
    echo ""
    echo "VISUALIZATION ERROR DETECTED: An error was encountered while attempting to generate the image for the Shortest Path within \"shortest_path_overlay.png\""
    echo "Please view the lines printed immediately above these to determine the potential nature of the detected errors"
    echo "For further information on feature access and troubleshooting please view the README: https://github.com/parsokev/graph_repo"
    echo ""
else
    echo "Success! The generated image of the SHORTEST PATH can now be viewed at \"graph_images/shortest_path_overlay.png\""
fi