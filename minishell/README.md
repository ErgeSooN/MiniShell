# minishell

<img width="863" alt="Ekran Resmi 2023-01-30 ÖS 3 07 15" src="https://user-images.githubusercontent.com/87010618/215487325-9d6f5ba0-4a83-4645-b2e7-20095f534cd0.png">

# Setup

Minishelli çalıştırmak için readline kütüphanesini indirmek gerekmektedir.

Kök dizinde bulunan .zshrc dosyanıza aşağıdaki fonksiyonu ekleyiniz (yoksa oluşturabilirsiniz).
Ardından '''source .zshrc''' komutunu çalıştırınız.

```
function brew_install()
{
	cd ~/goinfre
	mkdir homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew
	cd homebrew/bin && ./brew install readline
}
```
Ardından terminale `brew_install` yazarsanız readline kütüphanesini indirip kuracaktır.

Bu işlemler tamamlandıktan sonra Makefile dosyanızdaki `USERNAME` değişkenini kendi kullanıcı adınız ile değiştirin.

Bu adımlar tamamlandıktan sonra artık programı derleyebilirsiniz.

Bu proje, Bash programının bir taklidi olarak yazılmıştır. Proje, C dili kullanılarak Ecole 42'de geliştirilmiştir. Projenin amacı, Bash programlarının temel fonksiyonlarını taklit etmek ve execve fonksiyonunu kullanarak diğer programları çalıştırmaktır.

**Proje, aşağıdaki Bash komutlarının taklitlerini içermektedir**

- cd: Dizin değiştirmek için kullanılır.
- echo: Konsola bir metin yazdırmak için kullanılır.
- pwd: Geçerli dizinin yolunu yazdırmak için kullanılır.
- export: Sistem değişkenlerini oluşturmak veya değiştirmek için kullanılır.
- unset: Sistem değişkenlerini silmek için kullanılır.
- env: Sistem değişkenlerini listelemek için kullanılır.

**Ayrıca projede, aşağıdaki fonksiyonları kullanmaktadır**

- pipe: Bir komutun çıktısını başka bir komutun girdisi olarak kullanmayı sağlar.
- dup: Bir dosya tanıtıcısının çiftine yönlendirme yapar.
- dup2: Bir dosya tanıtıcısının çiftine yönlendirme yapar ve eski çifti kapatır.
- readline: Kullanıcıdan satır bazlı girdi almak için kullanılır.
- execve: Bir programı çalıştırmak için kullanılır.
- heredoc: Komut satırından okunan veriyi belirli bir formatta yazdırmak için kullanılır.

**Projeyi kurmak ve kullanmak için aşağıdaki adımları izleyin**

1. Projenin kaynak kodlarını GitHub sayfasından indirin veya klonlayın.
2. Projenin klasörüne gidin ve makefile kullanarak projeyi derleyin: make
3. Derleme işlemi tamamlandıktan sonra, projeyi çalıştırmak için aşağıdaki komutu kullanın:
./minishell

Proje, execve fonksiyonunu kullanarak çalıştırdığınız diğer programların çıktılarını görüntüler. Ayrıca taklit ettiğimiz Bash komutlarını kullanarak sistem üzerinde gezinmenizi ve değişkenleri yönetmenizi sağlar. Projede ayrıca pipe ve redir mantığını kullanarak çıktıların yönlendirilmesini ve heredoc fonksiyonu ile komut satırından veri alınmasını sağlar. Özellikle, "command1 | command2" gibi pipe kullanımı, "command1 > output.txt" gibi redirection kullanımı ve heredoc kullanımı gibi senaryolarda projenin nasıl çalıştığını gözlemleyebilirsiniz.

![Ekran Kaydı 2023-01-30 ÖS 3 09 41](https://user-images.githubusercontent.com/87010618/215487707-3c6cc7c9-d1b5-4bcc-83e5-34f9f31e9d96.gif)
