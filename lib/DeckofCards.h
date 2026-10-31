#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include "card.h"

/**
 * @brief Класс - колода карт
 * Колода хранит последовательность карт(первая - верхняя), не более MAX_SIZE карт
 * @param deck Колода карт
 * @param MAX_SIZE Максимальное количество карт в колоде
 */
class Deck_of_Cards{
    private:
    static const size_t MAX_SIZE=52;
    std::vector<Card> deck;
    void set_size(size_t size);
    public:
    /**
     * @brief Конструктор по умолчанию, создаёт пустую колоду
     */
    Deck_of_Cards()=default;

    /**
     * @brief Инициализирующий конструктор, создаёт колоду заданного размера cо случайными картами
     * @param s Размер колоды (от 0 до MAX_SIZE)
     * @throw std::invalid_argument если размер колоды > MAX_SIZE
     */
    explicit Deck_of_Cards(size_t s);

    /**
     * @brief Создаёт полную колоду из MAX_SIZE карт по одному разу
     * @return Deck_of_Cards  Полная колода карт (упорядоченная)
     */
    static Deck_of_Cards full_deck();

    /**
     * @brief Перегрузка оператора [], доступ к карте по индексу
     * @param x индекс карты
     * @return Card&  ссылка на карту из колоды по переданному индексу
     * @throw std::out_of_range если x>= размера колоды
     */
    Card& operator [] (size_t x);

    /**
     * @brief Перегрузка оператора [] для const колоды, доступ к карте по индексу
     * @param x Индекс карты
     * @return const Card& карта из колоды по переданному индексу
     * @throw std::out_of_range если x>= размера колоды
     */
    const Card& operator [] (size_t x) const;

    /**
     * @brief  Геттер, возвращающий размер колоды
     * @return size_t число от 0 до MAX_SIZE, количество карт в колоде
     */
    size_t get_size() const;

    /**
     * @brief Перегрузка для оператора +, объединение двух колод в новую
     * @param second Колода, с которой складываем
     * @return Deck_of_Cards новая колода
     * @throw std::invalid_argument если размер новой колоды > MAX_SIZE
     */
    Deck_of_Cards operator +(const Deck_of_Cards& second) const; 

    /**
     * @brief Перегрузка для оператора +=, добавление всех карт другой колоды в конец текущей
     * @param second Карта, с которой складываем
     * @return Deck_of_Cards Ссылку на текущую колоду
     * @throw std::invalid_argument если суммарный размер колоды > MAX_SIZE
     */
    Deck_of_Cards& operator +=(const Deck_of_Cards &second);

    /**
     * @brief Функция для сортировки колоды по масти, а потом по рангу
     */
    void sort();

    /**
     * @brief Функция для перемешивания колоды случайным образом
     */
    void shuffle();

    /**
     * @brief Функция, проверяющая наличие дубликатов в колоде
     * @return true, если есть дубликаты, false, если нет
     */
    bool have_duplicates() const;

    /**
     * @brief Функция, для добавления случайной карты в конец колоды
     * @throw std::invalid_argument если размер колоды >=MAX_SIZE
     */
    void add_random_card();

    /**
     * @brief Функция для добавления определённой карты в конец колоды
     * @param card Карта, которую добавляем в колоду
     * @throw std::invalid_argument если размер колоды >=MAX_SIZE
     * @throw std::invalid_argument если такая карта уже есть в колоде
     */
    void add_card(const Card& card);

    /**
     * @brief Функция для удаления карты из массива по индексу
     * @param x индекс удаляемой карты
     * @throw std::out_of_range если индекс не меньше, чем размер колоды
     */
    void remove_card_by_index(size_t x);

    /**
     * @brief Функция, для выделения  подгруппы карт по заданной масти
     * @param suit Масть, по которой фильтруем
     * @return Deck_of_Cards возвращает новую колоду
     * @throw std::invalid_argument если масть не является одной из 4 мастей
     */
    Deck_of_Cards filter_by_suit(const std::string& suit) const;

    /**
     * @brief Функция для переноса верхней (первой) карты из одной колоды в другую
     * @param first Колода, из которой карта удаляется
     * @param second Колода, в которую карта добавляется
     * @return Deck_of_Card возвращает ссылку на первую колоду
     * @throw std::out_of_range если первая колода пустая или вторая колода полная
     */
    friend Deck_of_Cards& operator >> (Deck_of_Cards& first, Deck_of_Cards& second);

    /**
     * @brief Перегрузка потока ввода
     * @param  is Поток ввода
     * @param deck Колода, в которую записываем результат
     * @return Ссылка на входной поток
     */
    friend std::istream& operator >> (std::istream& is, Deck_of_Cards& deck);
    
    /**
     * @brief Перегрузка потока вывода
     * @param  os Поток вывода
     * @param deck Колода, которую печатаем
     * @return Ссылка на выходной поток
     */
    friend std::ostream& operator << (std::ostream& os, const Deck_of_Cards& deck);
};

#endif