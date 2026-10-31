#include <catch2/catch_all.hpp>
#include "card.h"

TEST_CASE("Constructors of cards"){
    SECTION("Default constructor"){
        Card card;
        REQUIRE(card.get_rank()==1);
        REQUIRE(card.get_suit()==Suit::HEARTS);
    }

    SECTION("Initialization constructor"){
        Card card{"spades", 4};
        REQUIRE(card.get_rank()==4);
        REQUIRE(card.get_suit()==Suit::SPADES);
    }

    SECTION("Invalid rank"){
        REQUIRE_THROWS_AS(Card("spades", 344), std::invalid_argument);
    }

    SECTION("Invalid suit"){
        REQUIRE_THROWS_AS(Card("adsdkd",3), std::invalid_argument);
    }

    SECTION("Constructor with random values"){
        Suit suits[]={Suit::CLUBS, Suit::DIAMONDS,Suit::SPADES, Suit::HEARTS};
        int a=GENERATE(take(1, random(1,13)));
        int b=GENERATE(take(1, random(0,3)));
        Card card{Card::to_string(suits[b]),a};
        REQUIRE(card.get_rank()>=1);
        REQUIRE(card.get_rank()<=13);
        REQUIRE(card.get_suit()==suits[b]);
    }
}

TEST_CASE("Setters"){
    Card card;
    SECTION("Setters of rank and suit"){
        card.set_rank(13);
        REQUIRE(card.get_rank()==13);
        card.set_suit("spades");
        REQUIRE(card.get_suit()==Suit::SPADES);
    }

    SECTION("Errors in setter of rank"){
        REQUIRE_THROWS_AS(card.set_rank(34), std::invalid_argument);
    }

    SECTION("Error in setter of suit"){
        REQUIRE_THROWS_AS(card.set_suit("dskjdjsk"), std::invalid_argument);
    }
}

TEST_CASE("Random values"){
    Card card;
    std::string suits="hearts spades diamonds clubs";
    SECTION("Random rank"){
        card.random_values();
        REQUIRE(card.get_rank()>=1);
        REQUIRE(card.get_rank()<=13);
    }
    SECTION("Random suit"){
        const std::string suit=Card::to_string(card.get_suit());
        REQUIRE((suit=="hearts" || suit=="spades" || suit=="diamonds" || suit=="clubs"));
    }
}

TEST_CASE("Operators"){
    Card card;
    SECTION("Operator >>"){
        std::istringstream is("hearts 2");
        is >> card;
        REQUIRE(card.get_suit()==Suit::HEARTS);
        REQUIRE(card.get_rank()==2);
    }

    SECTION("Errors of operator >> of suit"){
        std::istringstream is("gfhghfdh 2");
        is >> card;
        REQUIRE(!is.good());
    }

    SECTION("Errors of operator >> of rank"){
        std::istringstream is("hearts 45");
        is >> card;
        REQUIRE(!is.good());
    }

    SECTION("Operator <<"){
        std::ostringstream os;
        Card card("spades", 3);
        os << card;
        REQUIRE(os.str().find("spades")!=std::string::npos);
        REQUIRE(os.str().find("3")!=std::string::npos);
    }

    SECTION("Operator <=>"){
        Card card1("hearts", 5);
        Card card2("hearts", 10);
        Card card3("spades", 5);
        Card card4("hearts", 5);
        REQUIRE(card1<card2);
        REQUIRE(card2>card1);
        REQUIRE(card1<=card2);
        REQUIRE(card2>=card1);
        REQUIRE((card1<=>card4)==std::partial_ordering::equivalent);
        REQUIRE((card1<=>card3)==std::partial_ordering::unordered);
    }

    SECTION("Operator =="){
        Card card1("hearts", 5);
        Card card2("hearts", 5);
        Card card3("spades", 5);
        Card card4("hearts", 10);
        REQUIRE(card1==card2);
        REQUIRE_FALSE(card1==card3);
        REQUIRE_FALSE(card2==card4);
    }
}

TEST_CASE("Format of output"){
    std::string suits[]={"hearts", "spades", "diamonds", "clubs"};
    std::string b_suit[] = {"♥", "♠", "♦", "♣"};
    std::string b_ranks[]   = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    SECTION("Beautiful rank"){
        for (int i=1; i<=13; i++){
            Card card("spades",i);
            REQUIRE(card.get_rank_beautiful()==b_ranks[i-1]);
        }
    }
    SECTION("Beautiful suit"){
        for (int j=0; j<4; j++){
            Card card(suits[j], 11);
            REQUIRE(card.get_suit_beautiful()==b_suit[j]);
        }
    }
    SECTION("Beautiful format"){
        for (int i=1; i<=13; i++){
            for (int j=0; j<4; j++){
                Card card(suits[j], i);
                REQUIRE(card.format()==b_ranks[i-1]+b_suit[j]);
            }
        }
    }
}