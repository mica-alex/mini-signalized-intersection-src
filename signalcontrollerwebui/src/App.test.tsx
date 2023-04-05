import React from 'react';
import {render, screen} from '@testing-library/react';
import {App} from './App';

test('renders Traffic Light Controller', () => {
    render(<App/>);
    const linkElement = screen.getByText(/Traffic Light Controller/i);
    expect(linkElement).toBeInTheDocument();
});
