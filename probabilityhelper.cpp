#include "probabilityhelper.h"
#include "utils.h"

// calculate chance of busting if player hits
double ProbabilityHelper::calculateBustChance(int handValue, const vector<string> &remainingCards)
{
    if (remainingCards.empty())
    {
        return 0.0;
    }

    int bustCards = 0;

    for (const auto &card : remainingCards)
    {
        int cardValue = getCardValue(card);

        if (handValue + cardValue > 21)
        {
            bustCards++;
        }
    }

    return static_cast<double>(bustCards) / remainingCards.size() * 100.0;
}

// suggest whether player should hit or stand
string ProbabilityHelper::getSuggestion(int handValue, const vector<string> &remainingCards)
{
    double bustChance = calculateBustChance(handValue, remainingCards);

    if (handValue <= 11)
    {
        return "Strongly suggest HIT. Bust chance: " + to_string(bustChance) + "%";
    }
    else if (bustChance < 35.0)
    {
        return "Consider HIT. Bust chance: " + to_string(bustChance) + "%";
    }
    else if (bustChance < 60.0)
    {
        return "Risky. Think carefully. Bust chance: " + to_string(bustChance) + "%";
    }
    else
    {
        return "Suggest STAND. Bust chance: " + to_string(bustChance) + "%";
    }
}