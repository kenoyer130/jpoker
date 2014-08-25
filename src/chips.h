#ifndef CHIPS_H
#define CHIPS_H

#include <cassert>

// wrapper for chips to make sure we don't go below 0
class Chips {

private:

	int chips {0};

public:
	
	void set(int startingChips) {
		this->chips = startingChips;
	}

	// removes the amount removed from chips.
	// if the bet would of reduced the chips below 0
	// the chips are reduced to 0 and the actual bet amount is removed
	// in texas hold em you can not go negative.
	int bet(int amount) {
		
		if((this->chips - amount) < 0) {
			amount = this->chips;
		}

		this->chips -= amount;

        assert (this->chips > -1);

        return amount;
	}

	int get() {
		return chips;
	}

    void add(int chips) {
      this->chips += chips;
    }
};

#endif /* CHIPS_H */
