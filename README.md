# react-native-turbo-array

# react-native-turbo-array

A high-performance array manipulation library for React Native, powered by C++ Turbo Modules. Perform complex array operations up to 10x faster than pure JavaScript implementations.

## Key Features

- 🚀 Native C++ implementation using Turbo Modules
- ⚡️ High-performance array operations
- 🔢 Advanced mathematical expressions support
- 🔄 Chainable operations
- 📊 Complex data transformations
- 🛠 Dynamic operation support
- 💾 Memory efficient
- 🌐 Cross-platform (iOS & Android)

## Why?

JavaScript array operations can become a bottleneck when dealing with large datasets or complex computations in React Native applications. This library moves these computations to the native layer using C++, providing significant performance improvements for:

- Data processing
- Mathematical computations
- Statistical analysis
- Real-time calculations
- Large dataset manipulations
- Complex filtering operations

## Performance

| Operation      | JavaScript | react-native-turbo-array | Improvement |
|----------------|------------|-------------------------|-------------|
| Map (10k items)| 150ms      | 15ms                    | 10x         |
| Filter         | 120ms      | 12ms                    | 10x         |
| Complex Chain  | 500ms      | 45ms                    | 11x         |

## Installation

```bash
npm install react-native-turbo-array
# or
yarn add react-native-turbo-array
```
## Usage


```ts
import TurboArray from 'react-native-turbo-array';

// Basic operations
const numbers = [1, 2, 3, 4, 5];

// Map with mathematical expression
const squared = await TurboArray.map(numbers, {
  expr: "x * x"
});

// Filter with condition
const filtered = await TurboArray.filter(numbers, {
  op: ">",
  value: 3
});

// Chain multiple operations
const result = await TurboArray.chain(numbers, [
  { type: "filter", condition: { op: ">", value: 2 } },
  { type: "map", operation: { expr: "x * 2" } },
  { type: "sort", comparator: { op: "desc" } }
]);

// Advanced mathematical expressions
const complex = await TurboArray.map(numbers, {
  expr: "x^2 + 2*x + sin(x)"
});
```



## Contributing

See the [contributing guide](CONTRIBUTING.md) to learn how to contribute to the repository and the development workflow.

## License

MIT

---

Made with [create-react-native-library](https://github.com/callstack/react-native-builder-bob)
