import SwitchComponent from './components/SwitchComponent';
import LedComponent from './components/LedComponent';
import '../node_modules/bootstrap/dist/css/bootstrap.min.css';
import './App.css';

function App() {
  return (
    <div>
      <div className="buttonLine">
        <SwitchComponent id="1"></SwitchComponent>
        <SwitchComponent id="2"></SwitchComponent>
        <SwitchComponent id="3"></SwitchComponent>
        <SwitchComponent id="4"></SwitchComponent>
        <SwitchComponent id="5"></SwitchComponent>
        <SwitchComponent id="6"></SwitchComponent>
        <SwitchComponent id="7"></SwitchComponent>
        <SwitchComponent id="8"></SwitchComponent>
      </div>
      <div className="buttonLine">
        <SwitchComponent id="9"></SwitchComponent>
        <SwitchComponent id="10"></SwitchComponent>
        <SwitchComponent id="11"></SwitchComponent>
        <SwitchComponent id="12"></SwitchComponent>
        <SwitchComponent id="13"></SwitchComponent>
        <SwitchComponent id="14"></SwitchComponent>
        <SwitchComponent id="15"></SwitchComponent>
        <SwitchComponent id="16"></SwitchComponent>
      </div>
      <div className="buttonLine">
        <SwitchComponent id="17"></SwitchComponent>
        <SwitchComponent id="18"></SwitchComponent>
        <SwitchComponent id="19"></SwitchComponent>
        <SwitchComponent id="20"></SwitchComponent>
        <SwitchComponent id="21"></SwitchComponent>
        <SwitchComponent id="22"></SwitchComponent>
        <SwitchComponent id="23"></SwitchComponent>
        <SwitchComponent id="24"></SwitchComponent>
      </div>
      <div className="buttonLine">
        <SwitchComponent id="25"></SwitchComponent>
        <SwitchComponent id="26"></SwitchComponent>
        <SwitchComponent id="27"></SwitchComponent>
        <SwitchComponent id="28"></SwitchComponent>
        <SwitchComponent id="29"></SwitchComponent>
        <SwitchComponent id="30"></SwitchComponent>
        <SwitchComponent id="31"></SwitchComponent>
        <SwitchComponent id="0"></SwitchComponent>
      </div>
      <div className="buttonLine">
        <LedComponent id="1"></LedComponent>
        <LedComponent id="2"></LedComponent>
        <LedComponent id="3"></LedComponent>
        <LedComponent id="4"></LedComponent>
        <LedComponent id="5"></LedComponent>
        <LedComponent id="6"></LedComponent>
        <LedComponent id="7"></LedComponent>
        <LedComponent id="8"></LedComponent>
        <LedComponent id="9"></LedComponent>
        <LedComponent id="10"></LedComponent>
        <LedComponent id="11"></LedComponent>
        <LedComponent id="12"></LedComponent>
        <LedComponent id="13"></LedComponent>
        <LedComponent id="14"></LedComponent>
        <LedComponent id="15"></LedComponent>
        <LedComponent id="16"></LedComponent>
      </div>
    </div>
    
  );
}

export default App;
