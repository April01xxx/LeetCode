/* 栈元素 */
struct StackRecord {
  char *elements;
  int capacity;
  int topofstack;
};

typedef struct StackRecord *Stack;

Stack
createStack(int size) {
  Stack s;

  s = malloc(sizeof(struct StackRecord));
  s->elements = malloc(size * sizeof(char));
  s->capacity = size;
  s->topofstack = -1;

  return s;
}

void
disposeStack(Stack s) {
  if (s) {
    free(s->elements);
    free(s);
  }
}

bool
isEmpty(Stack s) {
  return s->topofstack == -1;
}

bool
isFull(Stack s) {
  return s->capacity == (s->topofstack + 1);
}

void
push(Stack s, char c) {
  s->elements[++s->topofstack] = c;
}

char
pop(Stack s) {
  return s->elements[s->topofstack--];
}

bool
isValid(char *s) {
  size_t len;
  char c;
  Stack stack;

  if (s == NULL)
    return false;

  len = strlen(s);
  if (len & 0x1)
    return false;
  stack = createStack(len);
  while (*s != 0) {
    if (*s == '(' || *s == '[' || *s == '{')
      push(stack, *s);
    else {
      if (isEmpty(stack))
        return false;
      c = pop(stack);
      if (*s == ')' && c != '(')
        return false;
      if (*s == ']' && c != '[')
        return false;
      if (*s == '}' && c != '{')
        return false;
    }
    ++s;
  }
  if (isEmpty(stack)) {
    disposeStack(stack);
    return true;
  } else {
    disposeStack(stack);
    return false;
  }
}
