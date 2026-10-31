#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include "DeckofCards.h"

Deck_of_Cards::Deck_of_Cards(size_t s){
    if (s>MAX_SIZE) throw std::invalid_argument("Size of new deck must be under MAX_SIZE");
    deck=full_deck().deck;  
    shuffle();               
    set_size(s); 
}

Deck_of_Cards  Deck_of_Cards::full_deck(){
    Deck_of_Cards d;
    d.deck.reserve(MAX_SIZE);
    Suit suits[]={Suit::HEARTS, Suit::DIAMONDS,Suit::SPADES, Suit::CLUBS};
    for (int i=1; i<14; i++){
        for ( size_t j=0; j<4; j++){
            d.deck.emplace_back(suits[j], i);
        }
    }
    return d;
}

Card& Deck_of_Cards::operator [] (size_t x){
    if (x>=deck.size()) throw std::out_of_range("Value must be between 0 and size-1");
    return deck[x];
}

const Card& Deck_of_Cards::operator [] (size_t x) const{
    if (x>=deck.size()) throw std::out_of_range("Value must be between 0 and size-1");
    return deck[x];
}

size_t Deck_of_Cards::get_size() const{
    return this->deck.size();
}

void Deck_of_Cards::set_size(size_t size){
    if (size<=0 || size>MAX_SIZE) throw std::invalid_argument("Value must be between 1 and MAX_SIZE");
    this->deck.resize(size);
}

Deck_of_Cards Deck_of_Cards::operator + (const Deck_of_Cards& other) const{
    if (other.deck.size()+this->deck.size()> MAX_SIZE) throw std::invalid_argument("The sum of two decks over 52");
    Deck_of_Cards d;
    d.deck.resize(other.deck.size()+this->deck.size());
    auto it=std::copy(deck.begin(), deck.end(), d.deck.begin());
    std::copy(other.deck.begin(), other.deck.end(), it);
    return d;
} 

Deck_of_Cards& Deck_of_Cards::operator +=(const Deck_of_Cards &other){
    if (other.deck.size()+deck.size()>MAX_SIZE) throw std::invalid_argument("The sum of decks over 52");
    deck.insert(deck.end(), other.deck.begin(), other.deck.end());
    return *this;
}

void Deck_of_Cards::sort(){
    std::sort(this->deck.begin(), this->deck.end(), [](const Card& card1,const Card& card2){
        if (card1.get_suit()!=card2.get_suit()) return card1.get_suit() < card2.get_suit();
        return card1.get_rank() < card2.get_rank();
    });
}

void Deck_of_Cards::shuffle(){
    static std::mt19937 eng{std::random_device{}()};
    std::shuffle(deck.begin(), deck.end(), eng);
}

bool Deck_of_Cards::have_duplicates() const{
    for (size_t i=0; i<deck.size(); ++i){
        for (size_t j=i+1; j<deck.size(); ++j){
            if (deck[i]==deck[j]) return true;
        }
    }
    return false;
}

void Deck_of_Cards::add_card(const Card& card){
    if (deck.size()>=MAX_SIZE) throw std::invalid_argument("Deck is full");
    if (std::find(deck.begin(), deck.end(), card)!=deck.end()) throw std::invalid_argument("Duplicate card");
    deck.push_back(card);
}

void Deck_of_Cards::add_random_card(){
    if (deck.size()>=MAX_SIZE) throw std::invalid_argument("Deck is full");
    Card card;
    card.random_values();
    deck.push_back(card);
}

void Deck_of_Cards::remove_card_by_index(size_t x){
    if (x>=deck.size()) throw std::out_of_range("Index out of range");
    deck.erase(deck.begin()+x);
}

Deck_of_Cards Deck_of_Cards::filter_by_suit(const std::string& suit) const{
    Deck_of_Cards d;
    if (suit!="hearts" && suit!="spades" && suit!="diamonds" && suit!="clubs") throw std::invalid_argument("Invalid suit");
    d.deck.reserve(deck.size());
    std::copy_if(deck.begin(), deck.end(), std::back_inserter(d.deck), [&suit](const Card& card){
        return card.get_suit()==Card::from_string(suit);
    });
    return d;
}

Deck_of_Cards& operator >> (Deck_of_Cards& first, Deck_of_Cards& second){
    if (first.deck.empty()) throw std::out_of_range("First deck is empty");
    if (second.deck.size()>=Deck_of_Cards::MAX_SIZE) throw std::out_of_range("The second deck is full");
    Card card=*(first.deck.rbegin());
    first.deck.pop_back();
    second.deck.push_back(card);
    return first;
}

std::istream& operator >> (std::istream& is, Deck_of_Cards& deck){
    size_t size;
    is >> size;
    if (!is.good()) return is;
    if (size>Deck_of_Cards::MAX_SIZE){
        is.setstate(std::ios::failbit);
        return is;
    }
    Deck_of_Cards time;
    for (size_t i=0; i<size; ++i) {
        Card card;
        if (!(is >> card)){
            is.setstate(std::ios::failbit);
            return is;
        }
        time.deck.push_back(card);
    }
    deck=std::move(time);
    return is;
}

std::ostream & operator << (std::ostream& os, const Deck_of_Cards& deck){
    std::for_each(deck.deck.begin(),deck.deck.end(), [&os](const Card &card){
        os << "Suit of card:" << Card::to_string(card.get_suit()) << '\n';
        os << "Rank of card:" << card.get_rank() << std::endl;
    });
    return os;
}