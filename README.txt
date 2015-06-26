This module adds an extra tab to each field instance, allowing you to specify validation rules for your field instances.

The following validators are currently included (7.x-2.x):

Regular expression
Numeric values (optionally specify min and / or max value)
length (optionally specify min and / or max length)
number of words (optionally specify min and / or max words )
Plain text (disallow tags)
Must be empty (Anti-Spam: Hide with CSS)
Words blacklist
number of selections (optionally specify min and / or max selections )
Unique
Match against a field
Match against a property
Specific value(s)
Require at least one of several fields
Equal values on multiple fields
Unique values on multiple fields
PHP Code (powerfull but dangerous)
URL (support internal path and external url validation)
Email
Pattern (Regular expression lite)
Date range2
Following validators are included in sub module field validation extras:

Color(HTML5)
Date(ISO)
EAN number
Field collection unique
Integer values
IP Address
Numeric(HTML5, with the option to specify min/max/step)
Regular expression (Perl-Compatible)
Phone
Required field
Require some of several fields
Postal code(depend on Postal Code Validation, support Address Field)
Since 7.x-2.1, we add another sub module property validation which could solve validation issues for property(non-field), such as title, Ubercat SKU, list_price.

Requirements

Ctools
Entity API ( Property validation)
Documentation

Lullabot write a doc for this module:Write complex validation rules for your fields, http://www.lullabot.com/articles/module-monday-field-validation

Docs on drupal.org: http://drupal.org/node/1299698
Date range document: http://drupal.org/node/1438436
PHP code validator document: https://www.drupal.org/node/1537028

related modules

clientside validation
field validation deprecated
Acknowledgements

Mr Zhang need a validation module which could add regular expression validation rules for Field, and he think Webform Validation is simple and powerfull. But we can not find such a module. That is why original code of the Field validation 1.x module was copy from Webform Validation . Thanks to svendecabooter.

Sponsors:

This module was sponsored by FLTRP
Date validation module was sponsored by cgdrupalkwk
This module was sponsored by Think in Drupal
Token and basic conditional support was develped for sigmaxim.com
Authour:

Howard Ge

The author can be contacted for paid customizations of this module as well as Drupal consulting and development.
