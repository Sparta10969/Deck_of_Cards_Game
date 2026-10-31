#include <random>
#include <iostream>
#include "card.h"

std::string Card::to_string(const Suit suit) {
    switch (suit){
        case Suit::HEARTS:
            return "hearts";
        case Suit::CLUBS:
            return "clubs";
        case Suit::DIAMONDS:
            return "diamonds";
        case Suit::SPADES:
            return "spades";
    }
    throw std::invalid_argument("Invalid suit");
}

Suit Card::from_string(const std::string_view str) {
    if (str=="spades") return Suit::SPADES;
    if (str=="hearts") return Suit::HEARTS;
    if (str=="diamonds") return Suit::DIAMONDS;
    if (str=="clubs") return Suit::CLUBS;
    throw std::invalid_argument("Invalid suit");
}

bool Card::validate_suit(const std::string& s) noexcept{
    return s=="hearts" || s=="spades" || s=="diamonds" || s=="clubs";
}

bool Card::validate_rank(int r) noexcept{
    return r>=1 && r<=13;
}


Card::Card(const std::string& s, int r): suit(from_string(s)), rank(r){
    if (!validate_rank(r)) throw std::invalid_argument("Rank must be 1-13");
    if (!validate_suit(s)) throw std::invalid_argument("Invalid suit");
}

Card::Card(Suit s, int r): suit(s), rank(r){
    if (!validate_rank(r)) throw std::invalid_argument("Rank must be 1-13");
    if (!validate_suit(to_string(s))) throw std::invalid_argument("Invalid suit");
}

void Card::random_values(){
    static std::mt19937 eng{std::random_device{}()};
    static const Suit suits[]={Suit::HEARTS,Suit::SPADES,Suit::DIAMONDS, Suit::CLUBS};
    std::uniform_int_distribution rand_rank(1, 13);
    std::uniform_int_distribution rand_suit(0, 3);
    suit=suits[rand_suit(eng)];
    rank=rand_rank(eng);
}

int Card::get_rank() const noexcept{ 
    return rank; 
}

const Suit& Card::get_suit() const noexcept{
    return suit; 
}

void Card::set_rank(int r){
    if (!validate_rank(r)) throw std::invalid_argument("Rank must be 1-13");
    rank=r;
}

void Card::set_suit(std::string s){
    if (!validate_suit(s)) throw std::invalid_argument("Invalid suit");
    suit=from_string(s);
}

std::istream &operator >> ( std::istream& is, Card &c){
    int rank;
    std::string suit;
    is >> suit >> rank;
    if (is.fail()) return is;
    if (!Card::validate_rank(rank)){
        is.setstate(std::ios::failbit);
        return is;
    }
    if (!Card::validate_suit(suit)){
        is.setstate(std::ios::failbit);
        return is;
    }
    c.suit=Card::from_string(suit);
    c.rank=rank;
    return is;
}

std::ostream &operator << (std::ostream &os,const Card& c){
    os << "Suit of card: " << Card::to_string(c.suit)<< std::endl;
    os << "Rank of card: " << c.rank << std::endl;
    return os;
}

bool Card::operator== (const Card& comp) const noexcept{
    return suit==comp.suit && rank==comp.rank;
}

std::partial_ordering Card::operator <=> (const Card& c) const noexcept{
    if (c.suit!=suit) return std::partial_ordering::unordered;
    return rank <=> c.rank;
}

std::string Card::get_rank_beautiful() const {
    switch (rank){
        case 1: return "A";
        case 2: return "2";
        case 3: return "3";
        case 4: return "4";
        case 5: return "5";
        case 6: return "6";
        case 7: return "7";
        case 8: return "8";
        case 9: return "9";
        case 10: return "10";
        case 11: return "J";
        case 12: return "Q";
        case 13: return "K";
    }
    throw std::logic_error("Invalid rank");
}

std::string Card::get_suit_beautiful() const{
    if (suit==Suit::HEARTS) return "♥";
    if (suit==Suit::DIAMONDS) return "♦";
    if (suit==Suit::SPADES) return "♠";
    if (suit==Suit::CLUBS) return "♣";
    else throw std::logic_error("Invalid suit");
}

std::string Card::format() const{
    return get_rank_beautiful()+get_suit_beautiful();
}