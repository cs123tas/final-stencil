# Final Project

Project Plan:

Final Idea: L-system trees with burning on fractal terrains

Implementation Information + Resources:

L-system trees:

L-system is for Lindenmayer system. It applies a type of formal grammar: given an alphabet of symbols, a set of production rules that expand a symbol to a larger connection of symbols, and an initial “axiom”, L-system can recursively expand self-similar fractal-like forms. Given the fractal nature of trees, it is easy and concise to describe them with the L-system (trunk -> branch -> leaf). The core of the tree generation is the production rules, and they can be found in papers like https://www.bioquest.org/products/files/13157_Real-time%203D%20Plant%20Structure%20Modeling%20by%20L-System.pdf and https://www.academia.edu/33455723/Intelligent_tree_modeling_based_on_L_system. To make the tree look more realistic, we can use stochastic grammar, such as assigning different rules to one symbol with different probability of occurring (e.g. location of the branch on trunk or angle of the branch). In this way the generation result will not be deterministic. Also, by applying texture to the leaves and trunk of the tree, the final result will be even more realistic.

Burning:

For the fire effect, we are planning on implementing a series of particle emitters that are initialized at the position of the fuel sources on the tree (leaves, wood). This will mean we are able to realistically simulate the spread of fire across a tree since we will be able to “light” fuel sources adjacent to those that are already lit by instantiating new particle emitters at these positions. These particles will have several characteristics, including lifetime (particle will be killed when it reaches a certain lifetime), temperature (color, will also be killed once it is too cold), position, and velocity. We will also only spawn a certain number of particles at a time, since otherwise we will quickly run out of memory. During the meeting, I’d like to talk about methods we can use to ensure that these particles run smoothly and don’t glitch up the program or we run out of memory once there is too much fire. https://learnopengl.com/In-Practice/2D-Game/Particles  

Fractal terrain:

There is this presentation (https://cs.brown.edu/courses/cs123/handouts/final/final_asgn.pdf) that goes through several methods for generating fractal terrains. The algorithms included are the midpoint displacement method, the diamond square method, a method using the fast fourier transform, and the multifractal method. Since trees are often found on landscapes that do not have sudden ridges and peaks, we are thinking of using the fast fourier transform. This method appears to create smooth hills and flatter landscapes with greater ease.
The algorithm appears to be: generate random gaussian noise, apply the fast fourier transform, scale frequencies, apply the inverse fast fourier transform. Here is another resource with a version of the code written out in Mathematica https://www3.risc.jku.at/education/courses/ws2016/cas/landscape.html.


Project Flow:

When the project is run, a scene with computer generated trees on a fractal landscape will appear. In the window on the left where we can choose to turn on or off additional features, we will have the option to enable burning. When enabled, the user can click on a part of the tree or terrain and the fire will start there and spread according to particle emission equations. The user can click as many times as they want to start fires. When disabled, the previous burning will be cleared out and reset so that when enabled again there are no fires to start out with.

Division of Labor:

Since there are three features we are trying to implement, we are thinking of each taking charge of one feature. Monica will do the fractal terrain, Ao will do the L-system trees, and Connor will do the burning. Since some of these features seem more complicated than others, once one person finishes their part, they will help with the other ones. We expect burning to be the most complicated.

