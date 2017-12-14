==========
Class method registration
==========

<?php
echo "hi"

// Following class definition should fail, but cannot test
?>

---

(program  (class_declaration (name) (method_declaration (function_definition (name) (compound_statement)))) (class_declaration (name) (class_base_clause (qualified_name (name))) (method_declaration (function_definition (name) (compound_statement)))) (class_declaration (name) (class_base_clause (qualified_name (name))) (method_declaration (function_definition (name) (compound_statement)))) (class_declaration (name) (class_base_clause (qualified_name (name)))) (class_declaration (name) (class_base_clause (qualified_name (name))) (method_declaration (function_definition (name) (compound_statement)))) (comment) (comment) (echo_statement (string)))