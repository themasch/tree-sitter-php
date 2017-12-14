#include "tree_sitter/parser.h"
#include <wctype.h>

enum TokenType {
  AUTOMATIC_SEMICOLON,
  COMMENT
};

void *tree_sitter_php_external_scanner_create() { return NULL; }
void tree_sitter_php_external_scanner_destroy(void *p) {}
void tree_sitter_php_external_scanner_reset(void *p) {}
unsigned tree_sitter_php_external_scanner_serialize(void *p, char *buffer) { return 0; }
void tree_sitter_php_external_scanner_deserialize(void *p, const char *b, unsigned n) {}

static inline void advance(TSLexer *lexer) { lexer->advance(lexer, false); }

static bool scan_whitespace_and_comments(TSLexer *lexer) {
  for (;;) {
    while (iswspace(lexer->lookahead)) {
      advance(lexer);
    }

    if (lexer->lookahead == '/') {
      advance(lexer);

      if (lexer->lookahead == '/') {
        advance(lexer);
        while (lexer->lookahead != 0 && lexer->lookahead != '\n') {
          advance(lexer);
        }
      } else {
        return false;
      }
    } else {
      return true;
    }
  }
}

bool tree_sitter_php_external_scanner_scan(void *payload, TSLexer *lexer,
                                                  const bool *valid_symbols) {
    if (valid_symbols[AUTOMATIC_SEMICOLON]) {
      lexer->result_symbol = AUTOMATIC_SEMICOLON;
      // Mark the end of a scanned token.
      lexer->mark_end(lexer);

      // if (!scan_whitespace_and_comments(lexer)) return false;
      while (iswspace(lexer->lookahead)) {
        advance(lexer);
      }
      if (lexer->lookahead == '?') {
        advance(lexer);

        return lexer->lookahead == '>';
      }
    }

      lexer->result_symbol = COMMENT;

      while (iswspace(lexer->lookahead)) {
        lexer->advance(lexer, true);
      }

      if (lexer->lookahead == '#') {
        advance(lexer);

      } else if (lexer->lookahead == '/') {
        advance(lexer);
        if (lexer->lookahead == '/') {
          advance(lexer);
        } else {
          return false;
        }
      } else {
        return false;
      }

      while (lexer->lookahead != '\n' && lexer->lookahead != 0) {
        advance(lexer);
      }

      lexer->mark_end(lexer);
      return true;
}

