#include <vector>
#include "DeckofCards.h"
#include "card.h"
#include "dialogue_functions.h"

std::vector<void(*)(Deck_of_Cards&)> processors={nullptr, dialog_create_card, dialog_create_random_card, dialog_compare_two_cards, dialog_show_card_beautifully, dialog_create_random_deck, dialog_create_full_deck, dialog_show_deck, dialog_add_random_card, dialog_remove_card, dialog_get_card, dialog_sort_deck,
dialog_shuffle_deck, dialog_merge_decks, dialog_check, dialog_get_group};

const std::string messages[]= {
    "0. Quit program",
    "1. Create card",
    "2. Create random card",
    "3. Compare two cards",
    "4. Show card in beautiful view",
    "5. Create random deck",
    "6. Create full deck",
    "7. Show deck",
    "8. Add random card to deck",
    "9. Remove card by index",
    "10. Get card by index",
    "11. Sort deck",
    "12. Shuffle deck",
    "13. Merge with another deck",
    "14. Check on duplicates",
    "15. Get group by suit"
};

int main(){
    Deck_of_Cards deck;
    size_t number;
    try{
        while ((number=dialog(messages, processors.size()))!=0){
            if (number>=processors.size()){
                std::cout << "Invalid choice, try again\n";
                continue;
            }
            processors[number](deck);
        }
    }catch(const Error_end_of_file&){
        std::cout << "End of input\n";
    }catch(const std::exception &e){
        std::cout << e.what() << std::endl;
    }
    std::cout << "End of programm\n";
    return 0;
}