test_ActorGraph_exe = executable('test_ActorGraph.cpp.executable', 
    sources: ['test_ActorGraph.cpp'], 
    dependencies : [ActorNode_dep, MovieNode_dep,ActorGraph_dep,Actor_dep, gtest_dep])
test('my ActorGraph test', test_ActorGraph_exe)


test_pathfinder_exe = executable('test_pathfinder.cpp.executable', 
    sources: ['test_pathfinder.cpp'], 
    dependencies : [ActorNode_dep, MovieNode_dep,ActorGraph_dep,Actor_dep, gtest_dep])
test('my pathfinder test', test_pathfinder_exe)

test_Actor_exe = executable('test_Actor.cpp.executable', 
    sources: ['test_Actor.cpp'], 
    dependencies : [ActorNode_dep, MovieNode_dep,ActorGraph_dep, Actor_dep,gtest_dep])
test('my Actor test', test_Actor_exe)

test_linkpredictor_exe = executable('test_linkpredictor.cpp.executable', 
    sources: ['test_linkpredictor.cpp'], 
    dependencies : [ActorNode_dep, MovieNode_dep,ActorGraph_dep, Actor_dep,gtest_dep])
test('my linkpredictor test', test_linkpredictor_exe)