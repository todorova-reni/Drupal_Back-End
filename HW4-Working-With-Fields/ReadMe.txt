Write a module that defines new field type “Example color”.
1.The field should have two widgets –hex code and colorpicker.
2.The field should print the following text: “The color for this event is [color]”. There should be two formatters -first: color the text; -second: color the background of the text.
3.The field should have a validation for hex code value using the following regular expression: '@^#[0-9a-f]{6}$@'
4.Every single field instance should color its own text or background.