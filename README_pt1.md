Used Cursor to debug why ships are not respecting placement rules for not being next to eachother.
Prompt: I am placing the ships now, but they are not taking eachother into account when getting placed, they are not supposed to be touching eachother. Can you help me debug whats going wrong?

Used Gemini for brainstorming about what type of variable to use for the coordinates, what I ended up settling on was string for input, convert it into two chars and then into unsigned shorts.

Used Cursor to debug why validateInput was making me always get the 'coordinates out of bounds' error.
Prompt: I am having an issue with the validateInput, it seems to be giving me the coordinate out of bounds warning even if I input coordinates that for sure exist on my board. could you please check what I am missing?