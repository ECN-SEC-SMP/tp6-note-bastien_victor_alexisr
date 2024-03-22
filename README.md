# OOP - Lab6

The goal of this lab is to implement the Monopoly game in C++.

## 1. Rules

The game uses symbolic money (monos), 32 houses, 12 hotels, cards, and two dice complete the game material. The game can be played by two to eight players. The game is played in turns, with two ordinary 6-sided dice. Each player rolls the dice, moves his token on the board, and then according to the box on which he stops performs a corresponding action:

- A land, a station or a public service belonging to no one: he then has the right to buy it. If he does not exercise his right of pre-emption, the banker puts the land up for auction without a predefined starting price.
- A land, a station or a public service belonging to him: nothing happens.
- A land, a station or a public service belonging to another player: he pays them the amount due for a night spent on this land (if the land, station or public service is mortgaged, the player pays nothing to the owner).
- Chance space: he draws a Chance card. This space does not necessarily bring good luck: it can indeed be a fine.
- Community Chest space: he draws a Community Chest card 
- Luxury tax space: he pays the amount to the bank.
- Start space: he earns 200 mono
- Income tax space: he pays 200 mono to the bank.
- Go to Jail space: the player goes directly to jail (by moving backwards and therefore without passing through the Start space).
- Simple visit space: neutral space where no action is taken.
- Jail space: he applies the rules to get out, and in the Monopoly edition, house rules, he no longer collects rent.
- Free Parking space: neutral space that does not bring any benefit to the player. A common practice is for the sums from taxes and fines to be placed in the middle of the board and collected by the player who lands on the Free Parking space, but this practice is not included in the classic Monopoly rules.

The properties are grouped by color. As soon as a player is in possession of all the properties of the same color, he is able to build houses and hotels there to increase the rent: the player therefore has a monopoly. He must build uniformly: there can be no more than one house difference between two properties of the same color. To obtain a hotel, you must first have placed 4 houses on each property of the same color. In addition, you can only build one hotel per property.

During the game, the player can end up in jail:

- by landing on the Go to Jail space;
- if he rolls doubles three times in a row (unable to perform any action after the last double);
- if he draws the Go to Jail card.
- When a player is in jail, they place their token on the Jail space. During this time, they do not play; they wait their turn until they are released, and they no longer collect rent on their properties. However, they can buy the card: Get Out of Jail Free from someone who owns it; it is up to the seller to negotiate the price. 

The player gets out of jail:

- if they have the Get Out of Jail Free card (they can either buy it or have kept it in reserve);
- if they roll doubles;
- if they pay a fine of 50 mono. The player cannot stay in jail for more than three turns. At that time, if they do not roll doubles, they are forced to pay the bail.

The winner is the last player who has not gone bankrupt and who therefore has a monopoly (but on the other hand no longer has any potential customers).