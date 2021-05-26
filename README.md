# Atom Soup
Particle simulation with simple rules, from which emerges continuous variant of cellular automata.

[![Example Simulation](http://img.youtube.com/vi/0NRJ3RAkCpE/0.jpg)](https://www.youtube.com/watch?v=0NRJ3RAkCpE)

Each atom type has specified weight (and optionally size) as well as attraction, repulsion or neutral relation with all atom types (including its own). Atom types are generated procedurally, so that different seed means not only different starting positions, but completely different atoms and interactions between them.

Note that since atom type A can be attracted to atom type B while atom type B can be repulsed by atom type A, the system DOES NOT follow the law of conservation of energy.

## SFML is required to run
