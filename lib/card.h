#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string> 
#include <stdexcept>
#include <compare>
#include <string_view>

enum  class Suit{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

/**
 * @brief Класс - игральная карта
 * 
 * suit Масть может быть 4 видов Suit::HEARTS, Suit::SPADES, Suit::DIAMONDS, Suit::CLUBS
 * rank Ранг карты, принимает значения от 1 до 13
 */

class Card{
    private:
    Suit suit=Suit::HEARTS;
    int rank=1;
    static bool validate_suit(const std::string& s) noexcept;
    static bool validate_rank(int r) noexcept;
    public:
    /**
     * @brief Преобразует масть в строку
     * @param suit Масть
     * @return std::string "hearts", "spades", "diamonds" или "clubs"
     * @throw std::invalid_argument если значение suit не является одной из 4 мастей
     */
    static std::string to_string(const Suit suit);

    /** @brief Преобразует строку в масть
     * @param str Строка "hearts", "spades", "diamonds" или "clubs"
     * @return Suit соответствующая масть
     * @throw std::invalid_argument если строка не является названием одной из 4 мастей
     */
    static Suit from_string(const std::string_view str);

    /**
     * @brief Конструктор по умолчанию: туз червей
     */
    Card()=default;

    /**
     * @brief Инициализирующий конструктор
     * @param s Масть (значение из Suit)
     * @param r Ранг: от 1 до 13
     * @throw std::invalid_argument если ранг вне диапазона от 1 до 13 или s не является одной из 4 мастей
    */
    Card(Suit s, int r);

    /**
     * @brief Инициализирующий конструктор
     * @param s Масть: {"hearts","spades","diamonds","clubs"}
     * @param r Ранг: от 1 до 13
     * @throw std::invalid_argument если ранг вне диапазона от 1 до 13 или suit не является одной из 4 мастей
     */
    Card(const std::string& s, int r);

    /**
     * @brief Функция, которая присваивает случайные масть и ранг карте
     */
    void random_values();

    /**
     * @brief Геттер, возвращающий ранг карты
     * @return int число от 1 до 13
     */
    int get_rank() const noexcept;

    /**
     * @brief Геттер, возвращающий масть карты
     * @return const Suit& одна из 4 мастей Suit::HEARTS, Suit::SPADES, Suit::DIAMONDS, Suit::CLUBS
     */
    const Suit& get_suit() const noexcept;

    /**
     * @brief Сеттер, который меняет ранг карты
     * @param  r Ранг: от 1 до 13
     * @throw std::invalid_argument если ранг вные диапазона от 1 до 13
     */
    void set_rank(int r);

    /**
     * @brief Сеттер, который меняет масть карты
     * @param s Масть: {"hearts","spades","diamonds","clubs"}
     * @throw std::invalid_argument если suit не является одной из 4 мастей
     */    
    void set_suit(std::string s);

    /**
     * @brief Перегрузка оператор для равенства карт
     * @param c Карта, с которой сравниваем
     * @return true, если совпадают масти и ранги у обеих, иначе false
     */
    bool operator ==(const Card& c) const noexcept;

    /**
     * @brief Сравнение карт, сравниваются только в случае одной масти, если разные масти, то карты считаются несравнимыми
     * @param c Карта, с которой сравниваем
     * @return std::partial_ordering:: less если *this < c по рангу; greater, если >; 
     * equivalent, если равны; unordered, если масти разные.
     */
    std::partial_ordering operator <=> (const Card& c) const noexcept;

    /**
     * @brief Чтение карты из потока ввода (формат "масть ранг")
     * @param is Поток ввода
     * @param c Карта, в которую записываем результат
     * @return Ссылка на входной поток
     */
    friend std::istream& operator >> (std::istream &is, Card& c);

    /**
     * @brief Печать карты из потока вывода 
     * @param os Поток вывода
     * @param c Карта, которую печатаем
     * @return Ссылка на выходной поток
     */
    friend std::ostream& operator << (std::ostream &os, const Card& c);

    /**
     * @brief Функция для "красивого" формата ранга
     * @return std::string "A","2","3","4","5","6","7","8","9","10","J","Q","K"
     * @throw std::logic_error если ранг вне диапазона от 1 до 13
     */
    std::string get_rank_beautiful() const;

    /**
     * @brief Функция для "красивого" формата масти
     * @return std::string "♥", "♠", "♦", "♣"
     * @throw std::logic_error если масть не является одной из 4
     */
    std::string get_suit_beautiful() const;

    /**
     * @brief Функция для "красивого" формата карты
     * @return std::string "rank_beautiful|suit_beautiful"
     * @throw std::logic_error если масть или ранг некорректны
    */
    std::string format() const;
};

#endif