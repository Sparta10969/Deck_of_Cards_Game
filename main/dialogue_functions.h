#ifndef DIALOGUE_FUNCTIONS_H
#define DIALOGUE_FUNCTIONS_H
#include "DeckofCards.h"

struct Error_end_of_file{};

int dialog(const std::string messages[], int amount);
void dialog_create_card(Deck_of_Cards &deck);
void dialog_create_random_card(Deck_of_Cards &deck);
void dialog_compare_two_cards(Deck_of_Cards &deck);
void dialog_show_card_beautifully(Deck_of_Cards &deck);
void dialog_create_random_deck(Deck_of_Cards &deck);
void dialog_create_full_deck(Deck_of_Cards &deck);
void dialog_show_deck(Deck_of_Cards &deck);
void dialog_add_random_card(Deck_of_Cards &deck);
void dialog_remove_card(Deck_of_Cards &deck);
void dialog_get_card(Deck_of_Cards &deck);
void dialog_sort_deck(Deck_of_Cards &deck);
void dialog_shuffle_deck(Deck_of_Cards &deck);
void dialog_merge_decks(Deck_of_Cards &deck);
void dialog_check(Deck_of_Cards &deck);
void dialog_get_group(Deck_of_Cards &deck);

#endif