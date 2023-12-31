//
// Created by Mateo on 22/11/2023.
//
#pragma once //ensures that we only compile this file once => no guards needed

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm> //functions: sort, find, count, ...
#include <stdexcept> //common exceptions
//using namespace std;



// This class represents a single production.
// A production is a replacement rule, it tells us which symbol
// to look for, and what (sequence of) symbol(s) to replace it with.
// The original symbol is usually called a “predecessor”.
// The (sequence of) symbol(s) is usually called a “successor”.

template <typename SymbolType>
class Production{
public:
    // constructor without any inputs
    Production(); // you can also do this with default, which implements it at the same time

    // constructor with call by reference, because you want your predecessor to change when you change its value.
    Production(const SymbolType& predecessor, const std::vector<SymbolType>& successor);

    // get predecessor = original symbol
    SymbolType getPredecessor() const;

    // get successor = the sequence of symbols
    std::vector<SymbolType> getSuccessor() const;

    //checks if the object production is equal to that of another object production
    bool operator==(const Production &difobject) const;

    SymbolType predecessor; // original symbol
    std::vector<SymbolType> successor; // sequence of symbol(s)
};


//definition of the member functions
template<typename SymbolType>
Production<SymbolType>::Production():predecessor(), successor() {}

template<typename SymbolType>
Production<SymbolType>::Production(const SymbolType& predecessor, const std::vector<SymbolType>& successor):predecessor(
        predecessor), successor(successor) {}

template<typename SymbolType>
SymbolType Production<SymbolType>::getPredecessor() const {
    return this->predecessor;
}

template<typename SymbolType>
std::vector<SymbolType> Production<SymbolType>::getSuccessor() const {
    return this->successor;
}

template<typename SymbolType>
bool Production<SymbolType>::operator==(const Production &difobject) const {
    return this->predecessor == difobject.predecessor;
}

template <typename SymbolType> //without this the unordered_set wouldn't work
struct std::hash<Production<SymbolType>> {

    size_t operator()(const Production<SymbolType>& production) const {
        return hash<SymbolType>{}(production.predecessor);
    }
};


// This function verifies that all symbols in the production
// (Predecessor and all symbols in the successor) are
// in the given alphabet.
// If all symbols are in the alphabet, this function returns true,
// otherwise, this function returns false.
// The time-complexity of this function should be O(N)
// where N is the total number of symbols in the production
// (predecessor + successors)
template <typename SymbolType>
bool isValidProduction(const Production<SymbolType>& production,const std::unordered_set<SymbolType>& alphabet){
    if (alphabet.count(production.getPredecessor()) == 0) {
        return false;
    }

    for (const auto& symbol : production.getSuccessor()) {
        if (alphabet.count(symbol) == 0){
            return false;
        }
    }
    return true;
}
// This class represents the actual L-System.
// It contains an axiom (Initial state), A set of productions
// (Replacement rules) and an alphabet (List of allowed symbols).
template <typename SymbolType>
class LSystemInterpreter{
private:
    std::unordered_set<SymbolType> alphabet;
    std::vector<SymbolType> axiom; // initial state
    std::unordered_set<Production<SymbolType>> productions;
    mutable std::vector<SymbolType> current; //because of mutable, member functions can change current even if they are const

    // This constructor takes an axiom, a set of productions and
    // an alphabet and stores these in the fields.
    // It should check that all productions are valid using
    // the “isValidProduction” function above.
    // If any of the productions are invalid,
    // it should throw an exception.
    // The constructor should also check that
    // every production has a unique predecessor.
    // It should also check that there is a Production for
    // each symbol in the alphabet.
    // If there is a symbol in the alphabet without a production,
    // you can decide what to do:
    // 1. Throw an exception
    // 2. Add an identity production (A -> A)
public:
    LSystemInterpreter(const std::vector<SymbolType>& axiom,const std::unordered_set<Production<SymbolType>>& productions,const std::unordered_set<SymbolType>& alphabet);
    // After `operator()` has been called one or more times,
    // the L-system will have accumulated an internal state.
    // This method should reset this internal state,
    // so the next call to `operator()` starts from
    // the L-system’s axiom again.
    void reset();
    // This function should execute a single iteration of the L-System.
    // When this method is called twice,
    // the second call should use the result of the first call
    // as its starting point.
    // This allows us to use `std::generate()` to iteratively
    // execute the L-System.
    //
    // Be careful when applying your productions!
    // Your productions should always be applied at the same time!
    // An example:
    // We have 2 productions: A -> AB, B -> A, and an axiom “ABA”
    // We can apply the first production first, and get:
    // “ABBAB”
    // And then we can apply the second production, to get:
    // “AAAAA”
    // THIS IS WRONG!
    //
    // You should always execute all productions on the original text!
    // So, in this case, the correct output would be:
    // “ABAAB”
    // (The first and last A’s were replaced by AB,
    // and the middle B by A)
    std::vector<SymbolType> operator() () const;
    std::vector<SymbolType> getCurrentState() const{ //this returns my current state, so i can write my text file
        return current;
    }
};
template<typename SymbolType>
LSystemInterpreter<SymbolType>::LSystemInterpreter(const std::vector<SymbolType> &axiom,
                                                   const std::unordered_set<Production<SymbolType>> &productions,
                                                   const std::unordered_set<SymbolType> &alphabet):
                                                   axiom(axiom), alphabet(alphabet), current(axiom) {
                    // after your constructor you need to check if all productions are valid
                    for (const auto& production: productions){ // & = call by reference (memory location)
                        if(!isValidProduction(production,alphabet)){
                            throw std::invalid_argument("The production is not valid! Contains symbols not declared in the alphabet");
                        }
                    }
                    this->productions = productions;
                    }

template<typename SymbolType>
void LSystemInterpreter<SymbolType>::reset() {
    this->current = this->axiom;
}

template <typename SymbolType>
std::vector<SymbolType> LSystemInterpreter<SymbolType>::operator()() const {
    std::vector<SymbolType> output;
    for (const auto& symbol: this->current) {
        bool productionFound = false;
        for (const auto& production : this->productions) {
            if (production.getPredecessor() == symbol) {
                // Ensure that getSuccessor returns a valid vector
                const auto& successor = production.getSuccessor();
                if (!successor.empty()) {
                    output.insert(output.end(), successor.begin(), successor.end());
                }
                productionFound = true;
            }
        }
        if (!productionFound) {
            // If no production was found, add the symbol itself to the output
            output.push_back(symbol);
        }
    }
    this->current = output;
    return output;
}