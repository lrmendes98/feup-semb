import ButtonComponent from './components/ButtonComponent';
import '../node_modules/bootstrap/dist/css/bootstrap.min.css';
import './App.css';

function App() {
  return (
    <div className="app">
      <ButtonComponent id="1"></ButtonComponent>
      <ButtonComponent id="2"></ButtonComponent>
      <ButtonComponent id="3"></ButtonComponent>
      <ButtonComponent id="4"></ButtonComponent>
    </div>
  );
}

export default App;
