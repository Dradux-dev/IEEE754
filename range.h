#pragma once

template <typename T>
struct Range {
    T first;
    T firstInvalid;
    T step;

    inline Range() = default;
    inline Range(const Range&) = default;

    inline Range(const T& start, const T& firstInvalid)
      : first(start),
        firstInvalid(firstInvalid),
        step(1)
    {}

    inline Range(const T& start, const T& firstInvalid, const T& step)
      : first(start),
        firstInvalid(firstInvalid),
        step(step)
    {}

    struct Iterator {
        const Range<T>& range;
        T current;

        inline Iterator(const Range<T>& range, const T& current)
          : range(range),
            current(current)
        {}

        void operator++() {
          if (range.first <= range.firstInvalid) {
            current += range.step;

            if (current > range.firstInvalid) {
              current = range.firstInvalid;
            }
          }
          else {
            current -= range.step;

            if (current < range.firstInvalid) {
              current = range.firstInvalid;
            }
          }
        }

        Iterator operator++(int) {
          T old = current;

          if (range.first <= range.firstInvalid) {
            current += range.step;

            if (current  > range.firstInvalid) {
              current = firstInvalid;
            }
          }
          else {
            current -= range.step;

            if (current < range.firstInvalid) {
              current = firstInvalid;
            }
          }

          return Iterator(range, old);
        }

        T operator*() const {
          return current;
        }

        T* operator->() const {
          return &current;
        }

        bool operator!=(const Iterator& r) {
          return (range.first != r.range.first || range.firstInvalid != r.range.firstInvalid || current != r.current);
        }
    };

    inline Iterator begin() {
      return Iterator(*this, first);
    }

    inline Iterator end() {
      return Iterator(*this, firstInvalid);
    }

    inline Iterator begin() const {
      return Iterator(*this, first);
    }

    inline Iterator end() const {
      return Iterator(*this, firstInvalid);
    }
};
