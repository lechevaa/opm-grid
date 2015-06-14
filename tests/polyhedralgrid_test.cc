#include "config.h"

#include <dune/grid/polyhedralgrid.hh>

#include <opm/parser/eclipse/Parser/Parser.hpp>
#include <opm/parser/eclipse/Deck/Deck.hpp>

#include <iostream>

const char *deckString =
    "RUNSPEC\n"
    "METRIC\n"
    "DIMENS\n"
    "10 10 10 /\n"
    "GRID\n"
    "DXV\n"
    "10*1 /\n"
    "DYV\n"
    "10*1 /\n"
    "DZ\n"
    "1000*1 /\n"
    "TOPS\n"
    "100*100.0 /\n";

template <class GridView>
void testGrid( const GridView& gridView )
{
  typedef typename GridView :: template Codim< 0 > :: Iterator Iterator;
  typedef typename GridView :: template Codim< 0 > :: Entity   Entity;
  typedef typename GridView :: IndexSet IndexSet;
  const IndexSet& indexSet = gridView.indexSet();
  for( Iterator it = gridView.template begin< 0 > (),
       end = gridView.template begin< 0 > (); it != end; ++it )
  {
    const Entity& entity = *it ;
    std::cout << "Entity[ " << indexSet.index( entity ) << " ] = "
              << entity.geometry().center() << std::endl;
  }
}

int main()
{
    Opm::Parser parser;
    const auto deck = parser.parseString(deckString);

    std::cout << deckString;

    std::vector<double> porv;
    typedef Dune::PolyhedralGrid< 3, 3 > Grid;
    Grid grid(deck, porv);

    testGrid( grid.leafGridView() );

    /*
    typedef Grid::LeafGridView GridView;
    typedef Grid::template Codim<0>::EntityIterator ElemIterator;
    typedef Grid::template Codim<0>::IntersectionIterator IsIt;

    GridView gridView = grid.leafGridView();

    int numElem = 0;
    ElemIterator elemIt = gridView.template begin<0>();
    ElemIterator elemEndIt = gridView.template end<0>();
    for (; elemIt != elemEndIt; ++elemIt) {
        if (std::abs(elemIt->geometry().volume() - 1.0) < 1e-8)
            std::cout << "element's " << numElem << " volume is wrong\n";

        int numIs = 0;
        IsIt isIt = elemIt->ibegin();
        IsIt isEndIt = elemIt->iend();
        for (; isIt != isEndIt; ++isIt) {
            if (isId->geometry().volume() != 1)
                std::cout << "intersection's " << numIs << " of element " << numElem << " volume is wrong\n";
            ++ numIs;
        }

        if (numIs != 6)
            std::cout << "number of intersections is wrong for element " << numElem << "\n";

        ++ numElem;
    }

    if (numElem != 10*10*10)
        std::cout << "number of elements is wrong: " << numElem << "\n";
        */


    return 0;
}
