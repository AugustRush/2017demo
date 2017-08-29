import XCTest

class BreadthFirstSearchTests: XCTestCase {

  func testExploringTree() {
    let tree = Graph()

    let nodeA = tree.addNode("a")
    let nodeB = tree.addNode("b")
    let nodeC = tree.addNode("c")
    let nodeD = tree.addNode("d")
    let nodeE = tree.addNode("e")
    let nodeF = tree.addNode("f")
    let nodeG = tree.addNode("g")
    let nodeH = tree.addNode("h")

    tree.addEdge(nodeA, neighbor: nodeB)
    tree.addEdge(nodeA, neighbor: nodeC)
    tree.addEdge(nodeB, neighbor: nodeD)
    tree.addEdge(nodeB, neighbor: nodeE)
    tree.addEdge(nodeC, neighbor: nodeF)
    tree.addEdge(nodeC, neighbor: nodeG)
    tree.addEdge(nodeE, neighbor: nodeH)

    let nodesExplored = breadthFirstSearch(tree, source: nodeA)

    XCTAssertEqual(nodesExplored, ["a", "b", "c", "d", "e", "f", "g", "h"])
  }

  func testExploringGraph() {
    let graph = Graph()

    let nodeA = graph.addNode("a")
    let nodeB = graph.addNode("b")
    let nodeC = graph.addNode("c")
    let nodeD = graph.addNode("d")
    let nodeE = graph.addNode("e")
    let nodeF = graph.addNode("f")
    let nodeG = graph.addNode("g")
    let nodeH = graph.addNode("h")
    let nodeI = graph.addNode("i")

    graph.addEdge(nodeA, neighbor: nodeB)
    graph.addEdge(nodeA, neighbor: nodeH)
    graph.addEdge(nodeB, neighbor: nodeA)
    graph.addEdge(nodeB, neighbor: nodeC)
    graph.addEdge(nodeB, neighbor: nodeH)
    graph.addEdge(nodeC, neighbor: nodeB)
    graph.addEdge(nodeC, neighbor: nodeD)
    graph.addEdge(nodeC, neighbor: nodeF)
    graph.addEdge(nodeC, neighbor: nodeI)
    graph.addEdge(nodeD, neighbor: nodeC)
    graph.addEdge(nodeD, neighbor: nodeE)
    graph.addEdge(nodeD, neighbor: nodeF)
    graph.addEdge(nodeE, neighbor: nodeD)
    graph.addEdge(nodeE, neighbor: nodeF)
    graph.addEdge(nodeF, neighbor: nodeC)
    graph.addEdge(nodeF, neighbor: nodeD)
    graph.addEdge(nodeF, neighbor: nodeE)
    graph.addEdge(nodeF, neighbor: nodeG)
    graph.addEdge(nodeG, neighbor: nodeF)
    graph.addEdge(nodeG, neighbor: nodeH)
    graph.addEdge(nodeG, neighbor: nodeI)
    graph.addEdge(nodeH, neighbor: nodeA)
    graph.addEdge(nodeH, neighbor: nodeB)
    graph.addEdge(nodeH, neighbor: nodeG)
    graph.addEdge(nodeH, neighbor: nodeI)
    graph.addEdge(nodeI, neighbor: nodeC)
    graph.addEdge(nodeI, neighbor: nodeG)
    graph.addEdge(nodeI, neighbor: nodeH)

    let nodesExplored = breadthFirstSearch(graph, source: nodeA)

    XCTAssertEqual(nodesExplored, ["a", "b", "h", "c", "g", "i", "d", "f", "e"])
  }

  func testExploringGraphWithASingleNode() {
    let graph = Graph()
    let node = graph.addNode("a")

    let nodesExplored = breadthFirstSearch(graph, source: node)

    XCTAssertEqual(nodesExplored, ["a"])
  }
}
