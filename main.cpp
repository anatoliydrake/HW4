#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

/*1. Добавить в контейнерный класс, который был написан в этом уроке, методы:
• для добавления элемента в конец массива (аналог функции pгыр_back() в векторах)
• для вывода на экран элементов.
также попробуйте реализовать оператор индексного доступа к элементу контейнера*/

class Container {
    int *data;
    int size;
public:
    Container() : size(0), data(nullptr) {}

    Container(int _size) : size(_size) {
        if (_size == 0) {
            Container();
        } else if (_size < 0) {
            printf("%s\n", "Bad things happened");
            Container();
        } else {
            data = new int[_size];
        }
        for (int i = 0; i < _size; ++i) {
            data[i] = 0;
        }
    }

    virtual ~Container() { delete[] data; }

    int get(int idx) { return data[idx]; }

    void set(int idx, int value) {
        data[idx] = value;
    }

    void insert(int value) {
        int *new_data = new int[size + 1];
        for (int i = 0; i < size; ++i)
            new_data[i] = data[i];
        new_data[size] = value;
        size++;
        data = new_data;
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            cout << data[i] << ' ';
        }
        cout << endl;
    }

    int &operator[](int idx) {
        assert(idx >= 0 && idx < size);
        return data[idx];
    }
};


/*2. Дан вектор чисел, требуется выяснить, сколько среди них различных.
 * Постараться использовать максимально быстрый алгоритм.*/

int countUnique(vector<int> &arr) {
    set<int> uArr;
    for (int i = 0; i < arr.size(); i++) {
        uArr.insert(arr[i]);
    }
    return uArr.size();
}

/*3. Реализовать класс Hand, который представляет собой коллекцию карт.
 * В классе будет одно поле: вектор указателей карт (удобно использовать вектор,
 * т.к. это по сути динамический массив, а тип его элементов должен быть - указатель на объекты класса Card).
 * Также в классе Hand должно быть 3 метода:
• метод Add, который добавляет в коллекцию карт новую карту, соответственно он принимает в качестве параметра указатель на новую карту
• метод Clear, который очищает руку от карт
• метод GetValue, который возвращает сумму очков карт руки (здесь предусмотреть возможность того, что туз может быть равен 11).*/

class Card {
public:
    enum Suits {
        DIAMONDS,
        HEARTS,
        CLUBS,
        SPADES
    };
    enum Ranks {
        ACE = 1,
        KING = 10,
        QUEEN = 10,
        JACK = 10,
        TEN = 10,
        NINE = 9,
        EIGHT = 8,
        SEVEN = 7,
        SIX = 6,
        FIVE = 5,
        FOUR = 4,
        THREE = 3,
        TWO = 2
    };

    Card(Ranks r, Suits s, bool f = true) : cardRank(r), cardSuite(s), face(f) {}

    void flip() {
        face = !face;
    }

    Ranks getValue() const {
        return cardRank;
    }

private:
    Ranks cardRank;
    Suits cardSuite;
    bool face;
};

class Hand {
    vector<Card *> m_Cards;
public:
    void Add(Card *pCard) {
        m_Cards.push_back(pCard);
    }

    void Clear() {
        m_Cards.clear();
    }

    int GetValue() {
        int result = 0;
        int countAces = 0;
        for (int i = 0; i < m_Cards.size(); ++i) {
            if (m_Cards[i]->getValue() == Card::ACE) {
                countAces++;
                continue;
            }
            result += m_Cards[i]->getValue();
        }
        if (countAces) {
            if (result + 11 + (countAces - 1) <= 21) {
                result += 11;
                countAces--;
            }
        }
        return result + countAces;
    }
};


int main() {
    Container container(3);
    container.print();
    container.set(1, 4);
    container.print();
    container.insert(7);
    container.print();
    cout << container[3] << endl;

    vector<int> array{1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    cout << "There are " << countUnique(array) << " unique items in your container" << endl;

    Card nine(Card::NINE, Card::CLUBS);
    Card ace(Card::ACE, Card::CLUBS);
    Hand hand;
    hand.Add(&nine);
    hand.Add(&ace);
    hand.Add(&ace);
    cout << hand.GetValue();
    return 0;
}
