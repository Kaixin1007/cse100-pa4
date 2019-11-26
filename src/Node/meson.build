
MovieNode_files = files(['MovieNode.hpp','ActorNode.hpp'])
MovieNode_includes = include_directories('.')

ActorNode_files = files([ 'ActorNode.hpp','MovieNode.hpp'])
ActorNode_includes = include_directories('.')

edge_files = files(['Edge.hpp', 'ActorNode.hpp','MovieNode.hpp'])
edge_includes = include_directories('.')

ActorNode = library('ActorNode', sources: ActorNode_files)
ActorNode_dep = declare_dependency(include_directories: ActorNode_includes,
   link_with: ActorNode)

MovieNode = library('MovieNode', sources: MovieNode_files)
MovieNode_dep = declare_dependency(include_directories: MovieNode_includes,
   link_with: MovieNode)

edge = library('Edge', sources: edge_files)
edge_dep = declare_dependency(include_directories: edge_includes,
   link_with: edge)