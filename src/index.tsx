import TurboArray from './NativeTurboArray';

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

export type AggregateResult = {
  sum?: number;
  avg?: number;
  min?: number;
  max?: number;
  count?: number;
  [key: string]: number | undefined;
};

// Core Array Operations
export function map(array: number[], operation: Operation): number[] {
  return TurboArray.map(array, operation);
}

export function filter(array: number[], condition: Operation): number[] {
  return TurboArray.filter(array, condition);
}

export function find(array: number[], condition: Operation): number {
  return TurboArray.find(array, condition);
}

export function reduce(
  array: number[],
  operation: Operation,
  initialValue: number
): number {
  return TurboArray.reduce(array, operation, initialValue);
}

// Advanced Operations
export function groupBy(
  array: number[],
  key: Operation
): { [key: string]: number[] } {
  return TurboArray.groupBy(array, key);
}

export function sortBy(array: number[], comparator: Operation): number[] {
  return TurboArray.sortBy(array, comparator);
}

export function chain(array: number[], operations: ChainOperation[]): number[] {
  return TurboArray.chain(array, operations);
}

export function aggregate(
  array: number[],
  operations: string[]
): AggregateResult {
  return TurboArray.aggregate(array, operations);
}

// Convenience Functions
export function sum(array: number[]): number {
  return reduce(array, { op: '+' }, 0);
}

export function average(array: number[]): number {
  const result = aggregate(array, ['avg']);
  return result.avg || 0;
}

export function square(array: number[]): number[] {
  return map(array, { expr: 'x * x' });
}

export function power(array: number[], exponent: number): number[] {
  return map(array, { expr: `x^${exponent}` });
}

// Mathematical Operations
export function sin(array: number[]): number[] {
  return map(array, { expr: 'sin(x)' });
}

export function cos(array: number[]): number[] {
  return map(array, { expr: 'cos(x)' });
}

export function sqrt(array: number[]): number[] {
  return map(array, { expr: 'sqrt(x)' });
}

export function abs(array: number[]): number[] {
  return map(array, { expr: 'abs(x)' });
}

// Utility Functions
export function range(start: number, end: number, step: number = 1): number[] {
  return Array.from(
    { length: Math.floor((end - start) / step) + 1 },
    (_, i) => start + i * step
  );
}

export function normalize(array: number[]): number[] {
  const stats = aggregate(array, ['min', 'max']);
  const min = stats.min || 0;
  const max = stats.max || 1;
  const valueRange = max - min;
  return map(array, { expr: `(x - ${min}) / ${valueRange}` });
}

// Export default object with all functions
export default {
  map,
  filter,
  find,
  reduce,
  groupBy,
  sortBy,
  chain,
  aggregate,
  sum,
  average,
  square,
  power,
  sin,
  cos,
  sqrt,
  abs,
  range,
  normalize,
};
