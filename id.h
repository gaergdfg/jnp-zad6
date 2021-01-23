#ifndef ID_H
#define ID_H


#include <string>
#include <stdexcept>


class Id {

public:
    Id(const char *_id) : id(_id) {
        if (id.size() == 0 || id.size() > 10) {
            throw std::invalid_argument("Invalid number of characters passed.");
        }
    }

    bool operator<(const Id &other) const { return id < other.id; }

private:
    std::string id;

};


#endif /* ID_H */
