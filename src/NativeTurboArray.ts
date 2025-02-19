import { TurboModuleRegistry } from 'react-native';
import type { TurboModule } from 'react-native';

export type Operation = {
  op?: string; // Basic operation type ('+', '-', '*', '/', '^', etc.)
  value?: number; // Value for basic operations
  field?: string; // Field for object operations
  expr?: string; // Mathematical expression (e.g., "x^2 + 2*x + 1")
};

export type ChainOperation = {
  type: 'map' | 'filter' | 'sort';
  operation?: Operation;
  condition?: Operation;
  comparator?: Operation;
};

export interface Spec extends TurboModule {
  // Core operations with expression support
  readonly map: (array: Array<number>, operation: Operation) => Array<number>;
  readonly filter: (
    array: Array<number>,
    condition: Operation
  ) => Array<number>;
  readonly find: (array: Array<number>, condition: Operation) => number;
  readonly reduce: (
    array: Array<number>,
    operation: Operation,
    initialValue: number
  ) => number;

  // Advanced operations
  readonly groupBy: (
    array: Array<number>,
    key: Operation
  ) => { [key: string]: Array<number> };
  readonly sortBy: (
    array: Array<number>,
    comparator: Operation
  ) => Array<number>;
  readonly chain: (
    array: Array<number>,
    operations: Array<ChainOperation>
  ) => Array<number>;
  readonly aggregate: (
    array: Array<number>,
    operations: Array<string>
  ) => {
    sum?: number;
    avg?: number;
    min?: number;
    max?: number;
    count?: number;
    [key: string]: number | undefined;
  };
}

const TurboArray: Spec = TurboModuleRegistry.getEnforcing<Spec>('TurboArray');

export default TurboArray;

// Usage examples:
/*
import TurboArray from './NativeTurboArray';

// Basic operations
const squares = await TurboArray.map(numbers, { expr: "x * x" });
const positives = await TurboArray.filter(numbers, { op: ">", value: 0 });

// Complex mathematical expressions
const complex = await TurboArray.map(numbers, {
  expr: "sin(x) + cos(x^2) + sqrt(abs(x))"
});

// Chaining operations
const result = await TurboArray.chain(numbers, [
  { type: "filter", condition: { expr: "x > 5" } },
  { type: "map", operation: { expr: "x * 2" } },
  { type: "sort", comparator: { op: "desc" } }
]);

// Grouping and aggregation
const groups = await TurboArray.groupBy(numbers, {
  expr: "floor(x / 10)" // Group by tens
});

const stats = await TurboArray.aggregate(numbers, [
  "sum", "avg", "min", "max", "count"
]);
*/
