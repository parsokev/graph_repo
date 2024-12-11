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

# Attempt to generate image of MST overlaying the entire processed graph using graphwiz
dot -Tpng:cairo ./dot_graphs/MST_overlay.gv -o ./graph_images/MST_overlay.png
if [ $? -ne 0 ]; then
    echo ""
    echo "VISUALIZATION ERROR DETECTED: An error was encountered while attempting to generate the image for the MST within \"MST_overlay.png\""
    echo "Please view the lines printed immediately above these to determine the potential nature of the detected errors"
    echo "For further information on feature access and troubleshooting please view the README: https://github.com/parsokev/graph_repo"
    echo ""
else
    echo "Success! The generated image of the MINIMUM SPANNING TREE can now be viewed at \"graph_images/MST_overlay.png\""
fi