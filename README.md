# golf-solitiare-console
This is an implementation of [Golf Solitaire](https://en.wikipedia.org/wiki/Golf_(patience)) using the Windows console as a platform, assembled entirely from C++.
<img width="412" height="268" alt="golfProgramScreen" src="https://github.com/user-attachments/assets/4a12c35d-0eb2-498e-b7a7-43ff2a63cb08" />

# Installation
1. Download the latest release of this repository.
2. Extract the files from the zipped folder.
3. Navigate to C:_Pathway*_\golf-solitiare-console-1.0\golf-solitiare-console-1.0\golfSolitaireConsole\bin\Debug and run golfSolitaireConsole.exe
# Controls
All inputs are entered into the console.

0,1,2,3,4,5,6 = columns of the tableau

All letter inputs are case-sensitive - uppercase D, U, R, Q, N do not work.
- d = draw from stock (face-down cards)
- u = undo move
- r = restart game
- q = quit game
- n = start a new game

# Rules / How to Play
A standard 52-card deck is split into a "tableau" consisting of 7 columns of 5 faceup cards, 1 faceup card as the base of the foundation, and 16 cards facedown to form the stock.

Each turn you can do one of the following:

- Take the bottom card of any one of the tableau's seven columns and put it on top of the wastepile. This can only be done under certain conditions.
- Draw a card from the stock, putting a new card on top of the wastepile.

The conditions under which a card in the tableau may be moved to the wastepile if it has a rank either one higher or one lower than the card on top of the foundation. The suit of the cards is irrelevant.

The ranks are orderered in standard order: **A 2 3 4 5 6 7 8 9 10 J Q K**. Although traditional versions of Golf prohibit the playing of Queens onto Kings and "wrapping" - playing Kings on top of Aces or Aces on top of Kings - my implementation is significantly more relaxed, allowing for both plays mentioned.

The objective of the game is to clear the tableau by playing all of the cards to the foundation. No redeals are allowed: if the talon is exhausted, cards are still present in the tableau, and no more possible moves exist, you lose the game, although you can always undo your moves to try alternate approaches.
