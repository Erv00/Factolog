# Language grammar
    main := (sync_module | async_module)+

    async_module := "async module" identifier "(" parameter_list_declaration "){" async_expression+ "}"

    identifier := (\alpha | "_") (\alnum | "_")*

    async_expression := var_declaration | module_connection | assignment

    var_declaration := "var" identifier (identifier ",")* ";"
    module_connection := identifier "(" parameter_list ");"
    assignment := identifier "=" (value | constant) ";"
